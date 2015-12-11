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

ENTIER=[0-9]+
LETTRE=[abc]
LETTRE_ENTIER=\\[0-9]+
OUVRANTE=\( /* -> [(] */
FERMANTE=\)
EOD=[\n\t\r ]


%%
<YYINITIAL> {
		
	{LETTRE}
		{return new Lettre(yytext());}
		
	{LETTRE_ENTIER}
		{return new Lettre(yytext().charAt(1) + "");}
		
	{ENTIER}
		{return new Entier(Integer.parseInt(yytext()));}
	      
	{OUVRANTE}
		{return new Ouvrante(true);}
	
	{FERMANTE}
	    {return new Fermante(true);} 
	    
	{EOD}
		{return new Eod(yytext());}
		
	.	
	{return new Unknown(yytext());}
}