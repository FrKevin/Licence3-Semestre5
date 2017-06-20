package jadelex;

%%

%class TokenizerV1
%implements Tokenizer
%public
%unicode
%line
%column
%{
	private int previousInt;
%}

%state COMMENTAIRE_MULTILIGNE
%state COMMENTAIRE_SIMPLE
%state STEP_ARG
%state JUMP_ARG
%state REPEAT

ENTIER_SIMPLE=[0-9]+

SEPARATEUR=[ \n\r\t]+
LEVER=LEVER|lever
BAISSER=BAISSER|baisser

NORD=NORD|nord
SUD=SUD|sud
EST=EST|est
OUEST=OUEST|ouest
PAS=PAS|pas
ALLER=ALLER|aller
FOIS=FOIS|fois

%%



<YYINITIAL> {
	{SEPARATEUR}
		{ }
	
	/* état du crayon */
	{LEVER}
		{ return new PenMode(false); }
	{BAISSER}
		{ return new PenMode(true); }
	
	/* Direction de dessin */
	{NORD}
		{ return new Move(jade.Direction.NORTH); }
	{SUD}
		{ return new Move(jade.Direction.SOUTH); }
	{EST}
		{ return new Move(jade.Direction.EAST); }
	{OUEST}
		{ return new Move(jade.Direction.WEST); }
	
	{PAS}
		{ yybegin(STEP_ARG); }
	
	{ALLER}
		{
			yybegin(JUMP_ARG);
			previousInt = -1;
		}
	
	{ENTIER_SIMPLE}
		{
			previousInt = Integer.parseInt(yytext());
			yybegin(REPEAT);
		}
		
	
	
	
	"/*"
		{ yybegin(COMMENTAIRE_MULTILIGNE); }
	
	"//"
		{ yybegin(COMMENTAIRE_SIMPLE); }
	
	.
		{ return new Unknown(yytext()); }
	
}

<COMMENTAIRE_MULTILIGNE>{
	[^*]+|[*][^/]
		{ }
	"*/"
		{ yybegin(YYINITIAL); }
}

<COMMENTAIRE_SIMPLE>{
	[^\n]+
		{ }
	"\n"
		{ yybegin(YYINITIAL); }
}

<STEP_ARG>{
	{SEPARATEUR}
		{ }
	{ENTIER_SIMPLE}
		{
			yybegin(YYINITIAL);
			return new StepLength(Integer.parseInt(yytext().trim()));
		}
	
	.
		{ return new Unknown(yytext()); }
}

<JUMP_ARG>{
	{SEPARATEUR}
		{ }
	{ENTIER_SIMPLE}
		{
			if (previousInt == -1) {
				previousInt = Integer.parseInt(yytext());
			}
			else {
				yybegin(YYINITIAL);
				return new Jump(previousInt, Integer.parseInt(yytext()));
			}
		}
	
	.
		{ return new Unknown(yytext()); }
}

<REPEAT>{
	{SEPARATEUR}
		{ }
	{FOIS}
		{
			yybegin(YYINITIAL);
			return new Repeat(previousInt);
		}
	
	.
		{ return new Unknown(yytext()); }
}

