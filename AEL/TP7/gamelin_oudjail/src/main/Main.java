package main;

import java.io.Reader;
import java.io.StringReader;

import java.util.Scanner;

import ard.Ard;
import ard.ArdExemple;
import ard.ParserException;
import ard.SyntaxException;
import condenses_lex.TokenizerArdExercice2;

public class Main {
	
	public static void menuArdPrint() {
		System.out.println("Choisissez un parser : (nombre)");
		System.out.println("	ArdExemple : 0");
		System.out.println("	ArdExercice1 : 1");
		System.out.println("	ArdExercice2 : 2");
		System.out.print("Parser ? > ");
	}
	
	public static int menuArd(Scanner sc) {
		int choice = -1;
		menuArdPrint();
		while (choice < 0 || choice > 2) {
			choice = sc.nextInt();
			if(choice < 0 || choice > 2) {
				menuArdPrint();
			}
		}
		sc.reset();
		return choice;
	}
	
	public static Ard mapArdInt(int number, Reader read) {
		switch (number) {
		case 0:
			return new ArdExemple(read);
		case 1:
			return new ArdExercice1(read);
		case 2:
			return new ArdExercice2(new TokenizerArdExercice2(read));
		default:
			return null;
		}
	}
	
	public static String description(int number) { /* Mal opti */
		return mapArdInt(number, new StringReader("")).toString();
	}
	
	public static void main(String[] args) throws SyntaxException, ParserException {
		Scanner input = new Scanner(System.in);
		int choiceMenuArd = menuArd(input);
		boolean first = true;
		System.out.println(description(choiceMenuArd));
		System.out.print("mot ? > ");
		while (input.hasNextLine()) {
			String word = input.nextLine();
			if(first) {
				first = false;
				continue;
			}
			Ard parser = mapArdInt(choiceMenuArd, new StringReader(word));
			try {
				parser.parse();
				System.out.println("OK");
			} catch (SyntaxException e) {
				System.out.println("Erreur : " + e.getMessage());
				//throw e;
			}
			System.out.print("mot ? > ");
		}
		input.close();
	}
}
