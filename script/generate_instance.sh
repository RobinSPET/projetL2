#!/bin/bash

# OBJECTIF :
#
# Créer un fichier contenant une nouvelle instance du problème,
# c'est-à-dire un ensemble de segments, générée aléatoirement.

# PARAMÈTRES DU SCRIPT :
#
# $1 nom du fichier à créer
# $2 nombre des segments de l'instance
# $3 paramètre utilisé pour définir le spectre des valeurs pour les abscisses et les ordonnées.
#    Il prend des valeurs dans l'intervalle [100,10000]. Alors, les valeurs des abscisses et
#    des ordonnées seront des entiers tirés aléatoirement sur l'intervalle [1, $3].


# FONCTION getNormalDistributionSample
#
# Génère de façon aléatoire un entier dans l'intervalle [min,max]
# selon la distribution normale.
#
# PARAMÈTRES : deux entiers correspondants aux limites de l'intervalle.

getNormalDistributionSample () {
	min=$1
	max=$2
	echo $(( min + (RANDOM % (max-min+1)) ))
}


# GESTION DE PARAMÈTRES
#
# Si :
# - le nombre de paramètres n'est pas correct, ou
# - le fichier indiqué par le paramètre $1 existe déjà, ou
# - le paramètre $3 n'est pas une valeur entière dans l'intervalle [100,10000],
# alors affichez un message d'erreur et arrêtez l'exécution du script.
# S'il n'y a pas d'erreur, affectez les paramètres aux variables globales
# (filename, n, range).

# TODO


# GÉNÉRATION DES SEGMENTS
#
# Dans la suite, cherchez et utilisez la commande "seq".
#
# Créez n segments (paramètre 2 du script). Chaque segment est composé par deux
# points. Écrivez les segments dans le fichier filename (paramètre 1 du script)
# en respectant le format présenté au cours.
#
# Pour créer un point, il faut utiliser la fonction getNormalDistributionSample
# et générer de façon aléatoire deux valeurs entières dans l'intervalle
# [1,range], qui correspondent à son abscisse et à son ordonnée,
# respectivement.
#
# Indication : chaque point créé doit être ajouté dans le tableau Points défini
# ci-dessous. Utilisez le format "abscisse/1,ordonnée/1" (conforme aussi au
# format du fichier à créer) pour stocker le point au tableau Points.
#
# Attention ! Si le point existe déjà dans le tableau, vous devez créer un
# nouveau point. Cela est répété autant de fois que besoin.
#
# Attention ! Si le segment créé est parallèle à l'axe des ordonnées, vous
# devez créer un nouveau segment. Cela est répété autant de fois que besoin.

# TODO