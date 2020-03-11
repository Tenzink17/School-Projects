package SparseVector;

import java.io.*;

public class Project1 {
	
	/*
	 * The main method will open the file project1.txt and have a loop to process each
	 *  sparse vector operation in the file.
	 *  The input consists of one or more sparse vector operations (add, subtract, dot) 
	 *  with each operation taking up 3 lines. A sparse vector operation consists of two 
	 *  sparse vectors and the operation to perform on the sparse vectors. 
	 *  The first sparse vector is on the first line, the second sparse vector is on the 
	 *  second line, and the operation is on the third line. A pair of numbers represents 
	 *  each element of the sparse vector, the element’s index followed by the element’s value. 
	 *  One or more spaces may separate each of the numbers of the sparse vector. 
	 *  An example sparse vector operation:
	 *  3 1.0 2500 6.3 5000 10.0 60000 5.7
	 *  An example sparse vector operation:
     *  3 1.0 2500 6.3 5000 10.0 60000 5.7
     *  1 7.5 3 5.7 2500 -6.3
     *  add
	 */
	public static void main(String[] args) {
		
		
		String line;
		SparseVector sv1;
		SparseVector sv2;
		SparseVector sv3;
		String op;
		
		try
		{
		FileInputStream fstream = new FileInputStream("project1.txt");
		
		BufferedReader br = new BufferedReader(new InputStreamReader(fstream));

		// read first line
	    line = br.readLine();
		
		while(line != null)
		{
		    // make sparse vector 1
		    sv1 = new SparseVector(line);
		    
			// read second line
		    line = br.readLine();
		    
		    // make sparse vector 2
		    sv2 = new SparseVector(line);
		    
		    // do operation
		    op = br.readLine();
		    
		    // add
		    if(op.equals("add"))
		    {
		    	// add vectors
		    	sv3 = sv1.add(sv2);
	
		    	// print output
		    	System.out.println(sv1.toString());
		    	System.out.println("+");
		    	System.out.println(sv2.toString());
		    	System.out.println("=");
		    	System.out.println(sv3.toString());
		    	System.out.println("");
		    }
		    
		    // subtract
		    else if(op.equals("subtract"))
		    {
		    	// subtract vectors
		    	sv3 = sv1.subtract(sv2);
		    	
		    	// print output
		    	System.out.println(sv1.toString());
		    	System.out.println("-");
		    	System.out.println(sv2.toString());
		    	System.out.println("=");
		    	System.out.println(sv3.toString());
		    	System.out.println("");
		    }
		    
		    // dot product
		    else if(op.equals("dot"))
		    {
		    	// dot vectors
		    	sv3 = sv1.dot(sv2);
		    	char dotCharacter = (char) 183;
		    	
		    	// print output
		    	System.out.println(sv1.toString());
		    	System.out.println(dotCharacter);
		    	System.out.println(sv2.toString());
		    	System.out.println("=");
		    	System.out.println(sv3.toString());
		    	System.out.println("");
		    }
		    
		    else
		    {
		    	System.out.println("unknown operation found: " + op);
		    }
		    line = br.readLine();
		}
		
		}
		catch(IOException ex)
		{
			System.out.println(ex.getMessage());
		}

	}
	


}
