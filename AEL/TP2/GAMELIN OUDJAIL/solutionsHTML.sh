#!/bin/sh
valeurAttribut='"([^"<&]|&[a-zA-Z:_][a-zA-Z0-9:_.-]*;)*"'

#q1
egrep --color=auto $valeurAttribut html/fil.html

#q2

nomXML='[a-zA-Z:_][a-zA-Z0-9:_.-]*'
refEntite='&[a-zA-Z:_][a-zA-Z0-9:_.-]*;'

baliseOuvrante="<$nomXML([[:space:]]$nomXML[[:space:]]*=[[:space:]]*$valeurAttribut)*[[:space:]]*>"

  #echo $baliseOuvrante
egrep --color=auto $baliseOuvrante html/fil.html

#Q3

egrep --color=auto '\+33[[:space:]]*\(0\)[[:space:]]*3(\.[0-9]{2}){4}+' html/*.html
