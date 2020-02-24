package InfixToPostfix;

public class DynamicArrayStack<AnyType> implements Stack<AnyType>
{
	public static final int DEFAULT_CAPACITY = 256;
	AnyType[] data;
	int topOfStack;

	public DynamicArrayStack() { this(DEFAULT_CAPACITY); }

	public DynamicArrayStack(int capacity)
	{
		topOfStack = -1;
		data = (AnyType[]) new Object[capacity];
	}

	public int size()
	{
		return topOfStack+1;
	}

	public boolean isEmpty()
	{
		return (topOfStack==-1);
 
	}

	public void push(AnyType newValue)
	{
		if(topOfStack==data.length-1)        // if stack is full resize the array
			resize(2*data.length);
		
		data[++topOfStack] = newValue;         // if not full insert it to the top
	}

	public AnyType top()
	{
		
		if(isEmpty())                                
			return null;
		else

			return data[topOfStack];
			
	}

	public AnyType pop()
	{
	
		if(isEmpty())                               
			return null;
		else
		
			return data[topOfStack--];
	}

	protected void resize(int newCapacity)
  {
		int n = size();

		AnyType[] temp = (AnyType[]) new Object[newCapacity];
		for (int i=0; i < n; i++)
		temp[i] = data[i];
		data = temp;
  }
}
