/* Exemple 1 */
package exemple1;

%%

%unicode

MOT_USUEL=[:letter:]+
ENTIER_SIMPLE=[0-9]+
OPERATEUR=\++|\*+|\-+|\/+
IDENTIFICATEUR=

%% 

{MOT_USUEL}|{ENTIER_SIMPLE}|{OPERATEUR}
      {return new Yytoken(yytext());}


[^[:letter:]0-9\++\*+\-+\/+]+
      {}  
