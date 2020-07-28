# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
# import os
# import sys
# sys.path.insert(0, os.path.abspath('.'))


# -- Project information -----------------------------------------------------

project = 'ecs-scenes'
copyright = '2020, Jacob Eriksson'
author = 'Jacob Eriksson'

# The full version, including alpha/beta/rc tags
release = '1.0.0'


# -- General configuration ---------------------------------------------------

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = [
    "breathe",
    "exhale"
]

# Add any paths that contain templates here, relative to this directory.
templates_path = ['_templates']

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']


# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = 'sphinx_rtd_theme'


# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = []

# Read The Docs HTML theme configuration
html_theme_options = {
    'collapse_navigation': False,
    'sticky_navigation': True,
    'navigation_depth': 6
}

# Language configuration
primary_domain = 'cpp'
highlight_language = 'cpp'

# Breathe extension configuration
breathe_projects = {
        'ecs-scenes': './doxygen/xml'
}
breathe_default_project = "ecs-scenes"

# Exhale extension configuration
def specificationsForKind(kind):
    '''
    For a given input ``kind``, return the list of reStructuredText specifications
    for the associated Breathe directive.
    '''
    # Change the defaults for .. doxygenclass:: and .. doxygenstruct::
    if kind == "class" or kind == "struct":
        return [
          ":members:",
          ":protected-members:",
          ":private-members:",
          ":undoc-members:"
        ]
    # An empty list signals to Exhale to use the defaults
    else:
        return []

# Use exhale's utility function to transform `specificationsForKind`
# defined above into something Exhale can use
from exhale import utils

exhale_args = {
    # These arguments are required
    "containmentFolder":      "./api",
    "rootFileName":           "index.rst",
    "rootFileTitle":          "Engine API",
    "fullApiSubSectionTitle": "API",
    "doxygenStripFromPath":   "..",
    "fullToctreeMaxDepth":    2,
    "createTreeView":         True,
    "exhaleExecutesDoxygen":  True,
    "exhaleUseDoxyfile":      True,
    "customSpecificationsMapping": utils.makeCustomSpecificationsMapping(
        specificationsForKind
    )
}
