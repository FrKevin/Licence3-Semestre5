doit_argent(anne,barbara).
doit_argent(barbara,cecile).
doit_argent(cecile,barbara).

evite(X,Y) :- doit_argent(X,Y).
evite(X,Z) :- doit_argent(X,Y), evite(Y,Z).

