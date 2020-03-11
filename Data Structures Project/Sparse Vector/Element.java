package SparseVector;

//Element class which stores the index and value of an element of a vector. 

public class Element implements Comparable <Element>{

	private int index;
	private double value;
	
	public Element(int index, double value) {

		this.index = index;
		this.value = value;
	}
	
	public int getIndex() {
		return index;
	}
	
	public void setIndex(int index) {
		this.index = index;
	}
	

	public double getValue() {
		return value;
	}
	
	public void setValue(double value) {
		this.value = value;
	}
	
	public String toString() {
		
		return "[" + index + "," +  value + "]";
	}

	public int compareTo(Element e) 
	{
		
		if(getIndex() > e.getIndex())
		{
			return 1;
		}
		else if (getIndex()< e.getIndex())
		{
			return -1;
		}
		else
		{
			return 0;
		}
	}

}

