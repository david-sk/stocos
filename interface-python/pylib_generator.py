#!/usr/bin/env python
#-*- coding: utf-8 -*-
# Python 3.7

# see : https://cpp.developpez.com/tutoriels/interfacer-cpp-python/
# python3.7 -m  pip install pygccxml pyplusplus

from pygccxml import parser
from pyplusplus import module_builder

# Configurations que vous pouvez avoir à changer sur votre système
generator_path = "/usr/bin/castxml"
generator_name = "castxml"
compiler = "gnu"
compiler_path = "/usr/bin/gcc" 

# Créé une configuration pour CastXML
xml_generator_config = parser.xml_generator_configuration_t(
    xml_generator_path=generator_path,
    xml_generator=generator_name,
    compiler=compiler,
    compiler_path=compiler_path)

# Liste de tous les fichiers d'en-tête de votre bibliothèque
header_collection = ["bonjour.hpp", "../sources/solution/solution.hpp"]

# Analyse les fichiers sources et créé un objet module_builder
builder = module_builder.module_builder_t(
    header_collection,
    xml_generator_path=generator_path,
    xml_generator_config=xml_generator_config)

# Détecte automatiquement les propriétés et les accesseurs/mutateurs associés
builder.classes().add_properties(exclude_accessors=True) 

# Définit un nom pour le module
builder.build_code_creator(module_name="pylib_auto")

# Écrit le fichier d'interface C++
builder.write_module('pylib_auto.cpp')#!/usr/bin/python
from pygccxml import parser
from pyplusplus import module_builder

# Configurations que vous pouvez avoir à changer sur votre système
generator_path = "/usr/bin/castxml"
generator_name = "castxml"
compiler = "gnu"
ompiler_path = "/usr/bin/gcc" 

# Créé une configuration pour CastXML
xml_generator_config = parser.xml_generator_configuration_t(
    xml_generator_path=generator_path,
    xml_generator=generator_name,
    compiler=compiler,
    compiler_path=compiler_path)

# Liste de tous les fichiers d'en-tête de votre bibliothèque
header_collection = ["Bonjour.hpp"]

# Analyse les fichiers sources et créé un objet module_builder
builder = module_builder.module_builder_t(
    header_collection,
    xml_generator_path=generator_path,
    xml_generator_config=xml_generator_config)

# Détecte automatiquement les propriétés et les accesseurs/mutateurs associés
builder.classes().add_properties(exclude_accessors=True) 

# Définit un nom pour le module
builder.build_code_creator(module_name="pylib_auto")

# Écrit le fichier d'interface C++
builder.write_module('pylib_auto.cpp')