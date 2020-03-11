package SparseVector;
import java.util.Iterator;

/**
 * SparseVector.java
 * A class called SparseVector which stores a sparse vector. A SparseVector is NOT a linked list. 
 * The SparseVector class has a data member which is a linked list storing the elements of a single 
 * sparse vector. A SparseVector does NOT store more than one sparse vector. Therefore, each instance
 * of a SparseVector stores a single unique sparse vector. Store the elements of the sparse vector 
 * in increasing index order.
 *
 */

public class SparseVector {
	

	DoublyLinkedList<Element> elements;
	
	public SparseVector()
	{
		elements = new DoublyLinkedList<Element>();
	}
	
	
	/*
	 *  constructor for the class, receives a string of numbers
	 *  A pair of numbers represents each element of the sparse vector, 
	 *  the element’s index followed by the element’s value. 
	 *  One or more spaces may separate each of the numbers of the sparse vector. 
	 *  The elements of the sparse vector should appear in increasing index order.
	 *  An example sparse vector input string:
     *  3 1.0 2500 6.3 5000 10.0 60000 5.7
	 */
	 public SparseVector(String line)
	 {
		 elements = new DoublyLinkedList<Element>();
		 
		 String[] fields  = line.split("\\s+");
		 
		 if(fields.length > 0)
		 {
			 
			 for(int i=0;i<fields.length;i=i+2)
			 {
				 Element e = new Element(Integer.parseInt(fields[i]), Double.parseDouble(fields[i+1]));
				 elements.add(e);
			 }
		 }
		 
		 
	 }
	
	/*
	 * The add method:
	 * performs the addition of two sparse vectors. 
	 * For example, if A and B are sparse vectors then A.add(B) returns a SparseVector which is A+B.
	 **/
	 
	public SparseVector add(SparseVector sv2)
	{
		Element e1=null, e2=null;
		double value = 0;
		
		SparseVector sv3 = new SparseVector ();
		
		// sv1 iterator
		Iterator<Element> itr1 = elements.iterator();
		
		// sv2 iterator
		Iterator<Element> itr2 = sv2.elements.iterator();
		
		boolean first = true;
		boolean second = true;
		
		while(itr1.hasNext() && itr2.hasNext())
		{
			// advance itertor 1
			if(first)
			{
			first = false;	
			e1 = (Element)itr1.next();
			}
			
			// advance itertor 2
			if(second)
			{
			second = false;
			e2 = (Element)itr2.next();
			}
			
			// e1 < e2 a1
			if(e1.getIndex() < e2.getIndex())
			{
				sv3.elements.add(new Element(e1.getIndex(),e1.getValue()));
				first = true;
			}
			
			// e2 < e1  b2
			else if(e2.getIndex() < e1.getIndex())
			{
				sv3.elements.add(new Element(e2.getIndex(),e2.getValue()));
				second=true;
			}
			
			// equal a1 + a2 
			else
			{
				value = e1.getValue() + e2.getValue();
				if(value != 0)
				{
					sv3.elements.add(new Element(e1.getIndex(),value));
				}
				
				first = true;
				second = true;
			}
			
		}
		
		// rest of sv1  a1
		while(itr1.hasNext())
		{
	     	e1 = (Element)itr1.next();	
			sv3.elements.add(new Element(e1.getIndex(),e1.getValue()));
		}
		
		// rest of sv2 b1
		while(itr2.hasNext())
		{
	     	e2 = (Element)itr2.next();	
			sv3.elements.add(new Element(e2.getIndex(),e2.getValue()));
		}
		
		return sv3;
	}
	
	
	/*
	 *  The subtract method:
	 *  performs the subtraction of two sparse vectors. 
	 *  For example, if A and B are sparse vectors then A.subtract(B) returns a SparseVector which is A-B.
	 */
	public SparseVector subtract(SparseVector sv2)
	{
		Element e1=null, e2=null;
		double value = 0;
		
		SparseVector sv3 = new SparseVector ();
		
		// sv1 iterator
		Iterator<Element> itr1 = elements.iterator();
		
		// sv2 iterator
		Iterator<Element>itr2 = sv2.elements.iterator();
		
		boolean first = true;
		boolean second = true;
		while(itr1.hasNext() && itr2.hasNext())
		{
			// advance itertor 1
			if(first)
			{
			first = false;	
			e1 = (Element)itr1.next();
			}
			
			// advance itertor 2
			if(second)
			{
			second = false;
			e2 = (Element)itr2.next();
			}
            
			// e1 < e2   a1
			if(e1.getIndex() < e2.getIndex())
			{
				sv3.elements.add(new Element(e1.getIndex(),e1.getValue()));
				first=true;
			}
			
			// e2 < e1  -b1
			else if(e2.getIndex() < e1.getIndex())
			{
				sv3.elements.add(new Element(e2.getIndex(),-e2.getValue()));
				second=true;
			}
			
			// equal  a1-a2
			else
			{
				value = e1.getValue() - e2.getValue();
				if(value != 0)
				{
					sv3.elements.add(new Element(e1.getIndex(),value));
				}
				
				first = true;
				second = true;
			}
			
		}
		
		// rest of sv1 a1
		while(itr1.hasNext())
		{
	     	e1 = (Element)itr1.next();	
			sv3.elements.add(new Element(e1.getIndex(),e1.getValue()));
		}
		
		// rest of sv2 -b1
		while(itr2.hasNext())
		{
	     	e2 = (Element)itr2.next();	
			sv3.elements.add(new Element(e2.getIndex(),-e2.getValue()));
		}
		
		return sv3;
	}
	

	
	/*
	 * The dot method
	 * which performs the dot product of two sparse vectors. 
	 * For example, if A and B are sparse vectors then A.dot(B) returns a double which is A.B.
	 */
	 public SparseVector dot(SparseVector sv2)
	 {
			Element e1=null, e2=null;
			double value = 0;
			
			SparseVector sv3 = new SparseVector ();
			
			// sv1 iterator
			Iterator<Element> itr1 = elements.iterator();
			
			// sv2 iterator
			Iterator<Element> itr2 = sv2.elements.iterator();
			
			boolean first = true;
			boolean second = true;
			
			while(itr1.hasNext() && itr2.hasNext())
			{
				// advance itertor 1
				if(first)
				{
				first = false;	
				e1 = (Element)itr1.next();
				}
				
				// advance itertor 1
				if(second)
				{
				second = false;
				e2 = (Element)itr2.next();
				}
				
				// e1 < e2
				if(e1.getIndex() < e2.getIndex())
				{
					first = true;
				}
				
				// e2 < e1
				else if(e2.getIndex() < e1.getIndex())
				{
					second = true;
				}
				
				// equal
				// dot product is a1 * b1 
				// only with same index
				else
				{
					value = e1.getValue() * e2.getValue();
					if(value != 0)
					{
						sv3.elements.add(new Element(e1.getIndex(),value));
					}
					
					first = true;
					second = true;
				}
				
			}
			
	
			return sv3;
	 }
	 
	
	 // The toString method to properly print a sparse vector. 
	 // The elements of the sparse vector must appear in increasing index order. 
	 // A sparse vector with no elements prints the string empty vector. 
	 // For example, if the sparse vector has the elements [1, 76.02], [4, -36.4], [5, 7.537], and [10, -2.19] 
	 // then the toString method would print
	 // ([1, 76.02], [4, -36.4], [5, 7.537], [10, -2.19]).
	 public String toString()
	 {
			Iterator<Element> itr = elements.iterator();
			String s = "(";
			Element e;
			
			while(itr.hasNext())
			{
				e = (Element)itr.next();
				s += e.toString();
			}
			
			return s + ")";
		 
	 }
	 

}
