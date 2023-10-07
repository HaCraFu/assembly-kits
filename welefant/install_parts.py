#!/usr/bin/env python3
import argparse
import logging
import os
import re
import sys
from textwrap import dedent
from typing import List

from easyeda2kicad import __version__
from easyeda2kicad.easyeda.easyeda_api import EasyedaApi
from easyeda2kicad.easyeda.easyeda_importer import (
    Easyeda3dModelImporter,
    EasyedaFootprintImporter,
    EasyedaSymbolImporter,
)
from easyeda2kicad.easyeda.parameters_easyeda import EeSymbol
from easyeda2kicad.helpers import (
    add_component_in_symbol_lib_file,
    get_local_config,
    id_already_in_symbol_lib,
    set_logger,
    update_component_in_symbol_lib_file,
)
from easyeda2kicad.kicad.export_kicad_3d_model import Exporter3dModelKicad
from easyeda2kicad.kicad.export_kicad_footprint import ExporterFootprintKicad
from easyeda2kicad.kicad.export_kicad_symbol import ExporterSymbolKicad
from easyeda2kicad.kicad.parameters_kicad_symbol import KicadVersion


def fp_already_in_footprint_lib(lib_path: str, package_name: str) -> bool:
    if os.path.isfile(f"{lib_path}/{package_name}.kicad_mod"):
        logging.warning(f"The footprint for this id is already in {lib_path}")
        return True
    return False


logging.basicConfig(level=logging.NOTSET)

output = "../lib/easyeda2kicad"
overwrite = False

kicad_version = KicadVersion.v6
sym_lib_ext = "kicad_sym"
api = EasyedaApi()

# Create new footprint folder if it does not exist
if not os.path.isdir(f"{output}.pretty"):
    os.makedirs(f"{output}.pretty")

# Create new 3d model folder if does not exist
if not os.path.isdir(f"{output}.3dshapes"):
    os.makedirs(f"{output}.3dshapes")

lib_extension = "kicad_sym"
if not os.path.isfile(f"{output}.{lib_extension}"):
    with open(
        file=f"{output}.{lib_extension}", mode="w+", encoding="utf-8"
    ) as my_lib:
        my_lib.write(
            dedent(
                """\
            (kicad_symbol_lib
                (version 20211014)
                (generator https://github.com/uPesy/easyeda2kicad.py)
            )"""
            )
            if kicad_version == KicadVersion.v6
            else "EESchema-LIBRARY Version 2.4\n#encoding utf-8\n"
        )

with open(sys.argv[1]) as f:
    lines = f.read().splitlines()
    components = map(lambda x: x.split()[0], lines)  # only first word
    components = filter(lambda x: not x.startswith(
        "#"), components)  # remove commented lines
    for component_id in components:
        logging.info(f"component {component_id}")
        cad_data = api.get_cad_data_of_component(lcsc_id=component_id)

        # ---------------- SYMBOL ----------------
        importer = EasyedaSymbolImporter(easyeda_cp_cad_data=cad_data)
        easyeda_symbol: EeSymbol = importer.get_symbol()
        # print(easyeda_symbol)

        is_id_already_in_symbol_lib = id_already_in_symbol_lib(
            lib_path=f"{output}.{sym_lib_ext}",
            component_name=easyeda_symbol.info.name,
            kicad_version=kicad_version,
        )

        if not overwrite and is_id_already_in_symbol_lib:
            logging.info(f"skipping existing part {component_id}")
            continue

        exporter = ExporterSymbolKicad(
            symbol=easyeda_symbol, kicad_version=kicad_version
        )
        # print(exporter.output)
        kicad_symbol_lib = exporter.export(
            footprint_lib_name=output.split("/")[-1].split(".")[0],
        )

        if is_id_already_in_symbol_lib:
            update_component_in_symbol_lib_file(
                lib_path=f"{output}.{sym_lib_ext}",
                component_name=easyeda_symbol.info.name,
                component_content=kicad_symbol_lib,
                kicad_version=kicad_version,
            )
        else:
            add_component_in_symbol_lib_file(
                lib_path=f"{output}.{sym_lib_ext}",
                component_content=kicad_symbol_lib,
                kicad_version=kicad_version,
            )

        logging.info(
            f"Created Kicad symbol for ID : {component_id}\n"
            f"       Symbol name : {easyeda_symbol.info.name}\n"
            f"       Library path : {output}.{sym_lib_ext}"
        )

        # ---------------- FOOTPRINT ----------------
        importer = EasyedaFootprintImporter(easyeda_cp_cad_data=cad_data)
        easyeda_footprint = importer.get_footprint()

        is_id_already_in_footprint_lib = fp_already_in_footprint_lib(
            lib_path=f"{output}.pretty",
            package_name=easyeda_footprint.info.name,
        )
        if not overwrite and is_id_already_in_footprint_lib:
            logging.info(f"skipping existing part {component_id}")
            continue

        ki_footprint = ExporterFootprintKicad(footprint=easyeda_footprint)
        footprint_filename = f"{easyeda_footprint.info.name}.kicad_mod"
        footprint_path = f"{output}.pretty"
        model_3d_path = f"{output}.3dshapes".replace("\\", "/")
        model_3d_path = "${KIPRJMOD}/" + model_3d_path

        ki_footprint.export(
            footprint_full_path=f"{footprint_path}/{footprint_filename}",
            model_3d_path=model_3d_path,
        )

        logging.info(
            f"Created Kicad footprint for ID: {component_id}\n"
            f"       Footprint name: {easyeda_footprint.info.name}\n"
            f"       Footprint path: {os.path.join(footprint_path, footprint_filename)}"
        )

        # ---------------- 3D MODEL ----------------
        exporter = Exporter3dModelKicad(
            model_3d=Easyeda3dModelImporter(
                easyeda_cp_cad_data=cad_data, download_raw_3d_model=True
            ).output
        )
        exporter.export(lib_path=output)
        if exporter.output:
            filename = f"{exporter.output.name}.wrl"
            lib_path = f"{output}.3dshapes"

            logging.info(
                f"Created 3D model for ID: {component_id}\n"
                f"       3D model name: {exporter.output.name}\n"
                f"       3D model path: {os.path.join(lib_path, filename)}"
            )
