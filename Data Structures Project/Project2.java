package InfixToPostfix;

import java.io.FileInputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Project2 {

	/**
	 * The main method will open the file project2.txt and have a loop to
	 * process each arithmetic expression (line) in the file. The main method
	 * will pass the line of text to the InfixToPostfix class to perform the
	 * conversion to postfix notation
	 */
	public static void main(String[] args) {

		InfixToPostfix itp = new InfixToPostfix();

		try {
			FileInputStream fstream = new FileInputStream("project2.txt");

			BufferedReader br = new BufferedReader(new InputStreamReader(
					fstream));

			String infix = br.readLine();
	
			while (infix != null) {
			
				System.out.println(infix);
				
				String postfix = itp.convertToPostfix(infix);

				System.out.println(postfix);
				System.out.println("");
				
				infix = br.readLine();
			}
		} 

		catch (IOException ex) {
			System.out.println(ex.getMessage());
		}

	}
}
