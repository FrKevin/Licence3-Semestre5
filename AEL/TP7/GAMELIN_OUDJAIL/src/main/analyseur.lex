package condenses_lex;

import condenses_lex.Entier;
import condenses_lex.Lettre;
import condenses_lex.Ouvrante;
import condenses_lex.Fermante;
import condenses_lex.Eod;
import condenses_lex.Unknown;
import condenses_lex.Tokenizer;


%%

%class TokenizerArdExercice2
%implements Tokenizer
%public
%unicode
%line
%column

LETTRE=[abc]+
ENTIER=[0-9]+
OUVRANTE=\( /* -> [)] */
FERMANTE=\)
EOD=[\n\t\r ]


%%
<YYINITIAL> {
		
	{LETTRE}
		{return new Lettre(yytext());}
		
	{ENTIER}
		{return new Entier(Integer.parseInt(yytext()));}
	      
	{OUVRANTE}
		{return new Ouvrante(yytext());}
	
	{FERMANTE}
	    {return new Fermante(yytext());} 
	    
	{EOD}
		{return new Eod(yytext());}
		
	.	
	{return new Unknown(yytext());}
}