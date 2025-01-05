#!/bin/bash

# OBJECTIF :
#
# Réaliser une campagne expérimentale sur une collection des instances.

# PARAMÈTRES DU SCRIPT :
#
# $1 nom du répertoire contenant la collection des instances
# $2 nom du fichier avec les résultats


# GESTION DE PARAMÈTRES
#
# Testez si le nombre de paramètres est correct et affichez un message dans
# le cas contraire.
# Assurez vous que le premier paramètre correspond bien à un répertoire.

if [[ $# -ne 2 ]]; then
    echo "Usage: $0 <repertoire_collection> <fichier_resultats>"
    exit 1
fi

if [[ ! -d $1 ]]; then
    echo "Erreur : Le répertoire '$1' n'existe pas."
    exit 1
fi

# Affectation des paramètres aux variables.
collection_dir=$1
out_filename=$2

echo -n "" > "$out_filename"


# EXÉCUTION DE L'EXPÉRIENCE
#
# Pour toutes les instances de la collection, exécutez le programme "./expe".
# Il faut choisir comme sommet de depart le premier sommet du graphe
# (2eme ligne de chaque fichier).
# Pour chaque exécution, vous devez écrire une ligne dans le fichier
# $out_filename avec 6 colonnes :
# Colonne 1 : nombre des sommets du graphe
# Colonne 2 : paramètre concernant la densité du graphe
# Colonne 3 : numéro de l'instance avec ces paramètres
# Colonnes 4-5 : résultats obtenus par l'exécution du programme "./expe"
# Les colonnes sont séparées par une espace.

for instance_file in "$collection_dir"/*; do
    # Vérification du format du nom de fichier
    filename=$(basename -- "$instance_file")
    if [[ ! "$filename" =~ ^[0-9]+_[0-9]+_[0-9]+$ ]]; then
        echo "Avertissement : Le fichier '$filename' ne respecte pas le format attendu. Ignoré."
        continue
    fi

    # Extraire les informations depuis le nom du fichier
    nb_segments=$(echo "$filename" | cut -d'_' -f1)
    r=$(echo "$filename" | cut -d'_' -f2)
    instance_num=$(echo "$filename" | cut -d'_' -f3)

    # Exécuter ./expe avec uniquement le fichier d'instance
    expe_output=$(./script/expe "$instance_file")
    if [[ $? -ne 0 ]]; then
        echo "Erreur : L'exécution de ./expe sur '$instance_file' a échoué. Ignoré."
        continue
    fi

    # Extraire les résultats de ./expe
    result1=$(echo "$expe_output" | awk '{print $1}')
    result2=$(echo "$expe_output" | awk '{print $2}')

    # Vérification des résultats
    if [[ -z "$result1" || -z "$result2" ]]; then
        echo "Erreur : Résultats incomplets pour le fichier '$instance_file'. Ignoré."
        continue
    fi

    # Écrire les résultats dans le fichier de sortie
    echo "$nb_segments $r $instance_num $result1 $result2" >> "$out_filename"
done

echo "Campagne expérimentale terminée. Résultats enregistrés dans '$out_filename'."