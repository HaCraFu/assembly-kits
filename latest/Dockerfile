FROM ghcr.io/inti-cmnb/kicad7_auto:1.6.1
# FROM squidfunk/mkdocs-material:9
RUN apt-get update && apt-get install -y \
    python3-pip
RUN pip install \
    mkdocs-material \
    mike \
    mkdocs-static-i18n \
    mkdocs-minify-plugin \
    mkdocs-redirects

USER 1000