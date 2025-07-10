import esphome.codegen as cg
import esphome.config_validation as cv
import esphome.components.ledc.output as ledc_output
from esphome.components import output
from esphome.const import (
    CONF_ID,
)

moonled_ns = cg.esphome_ns.namespace("moontorch")
Moonled = moonled_ns.class_("Moonled", ledc_output.LEDCOutput)

CONFIG_SCHEMA = ledc_output.CONFIG_SCHEMA.extend({}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await output.register_output(var, config)