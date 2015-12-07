package exercices;

import condenses_lex.*;

%%

%class TokenizerEx2
%implements Tokenizer
%public
%unicode
%line
%column


ENTIER=[0-9]
LETTRE=[abc]
OUVRANTE=[(]
FERMANTE=[)]

%%



<YYINITIAL> {


	
	{ENTIER}
		{ return new Entier(Integer.parseInt(yytext())); }
	{LETTRE}
		{ return new Lettre(yytext()); }
	
	{OUVRANTE}
		{ return new Ouvrante(false); }
	{FERMANTE}
		{ return new Fermante(false); }
	
	[\n\r\t]
		{ return new Eod(yytext()); }
	
	
	.
		{ return new Unknown(yytext()); }
	
}

