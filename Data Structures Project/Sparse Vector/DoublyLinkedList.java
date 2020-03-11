package SparseVector;

import java.util.Iterator;
import java.util.ConcurrentModificationException;
import java.util.NoSuchElementException;

public class DoublyLinkedList<AnyType> implements List<AnyType>
{
  private static class Node<AnyType>
  {
    private AnyType data;
    private Node<AnyType> prev;
    private Node<AnyType> next;

    public Node(AnyType d, Node<AnyType> p, Node<AnyType> n)
    {
      setData(d);
      setPrev(p);
      setNext(n);
    }

    public AnyType getData() { return data; }

    public void setData(AnyType d) { data = d; }

    public Node<AnyType> getPrev() { return prev; }

    public void setPrev(Node<AnyType> p) { prev = p; }

    public Node<AnyType> getNext() { return next; }

    public void setNext(Node<AnyType> n) { next = n; }
  }

  private int theSize;
  private int modCount;
  private Node<AnyType> header;
  private Node<AnyType> trailer;

  public DoublyLinkedList()
  {
    header = new Node<AnyType>(null, null, null);
    trailer = new Node<AnyType>(null, null, null);
    modCount = 0;
    clear();
  }

  public void clear()
  {
    header.setNext(trailer);
    trailer.setPrev(header);
    theSize = 0;
  }

  public int size()
  {
    return theSize;
  }

  public boolean isEmpty()
  {
    return (size() == 0);
  }

  public AnyType get(int index)
  {
	  return getNode( index ).data;
  }

  public AnyType set(int index, AnyType newValue)
  {
      Node<AnyType> node = getNode( index );
      AnyType oldValue = node.data;
      node.data = newValue;   
      return oldValue;
  }

  public boolean add(AnyType newValue)
  {
    add(size(), newValue);
    return true;
  }

 //  add method, the index can be a value from 0 to size()
      
  public void add(int index, AnyType newValue)
  {
      Node<AnyType> node = getNode( index, 0, size( ) );
      
      if(node != null)
      {
      Node<AnyType> newNode =  new Node<AnyType>( newValue, node.prev, node );
      newNode.prev.next = newNode;
      node.prev = newNode;         
      theSize++;
      }
      
  }

  public AnyType remove(int index)
  {
    return remove(getNode(index));
  }

  public Iterator<AnyType> iterator()
  {
    return new LinkedListIterator();    
  }

  private Node<AnyType> getNode(int index)
  {
    return (getNode(index, 0, size()-1));
  }

  // This method returns the pointer to the node whose position in the list corresponds 
  // to the value of the parameter index. This method should ensure index is a value which
  // is greater than or equal to the parameter lower and less than or equal to the parameter 
  // upper.
  private Node<AnyType> getNode(int index, int lower, int upper)
  {

      Node<AnyType> node;
      
      // check bounds
      if( index < lower || index > upper )
          throw new IndexOutOfBoundsException( "index " + index + " out of bounds");
          
      
      // search from front
      if( index < size() / 2 )
      {
          node = header.next;
          for( int i = 0; i < index; i++ )
              node = node.next;            
      }
      
      // search from back
      else
      {
          node = trailer;
          for( int i = size( ); i > index; i-- )
              node = node.prev;
      } 
      
      return node; // return node

  }

  private AnyType remove(Node<AnyType> currNode)
  {
	  currNode.next.prev = currNode.prev;
	  currNode.prev.next = currNode.next;
      theSize--;
      return currNode.data;
  }

  private class LinkedListIterator implements Iterator<AnyType>
  {
    private Node<AnyType> current;
    private int expectedModCount;
    private boolean okToRemove;

    LinkedListIterator()
    {
      current = header.getNext();
      expectedModCount = modCount;
      okToRemove = false;
    }

    public boolean hasNext()
    {
      return (current != trailer);
    }

    public AnyType next()
    {
      if (modCount != expectedModCount)
        throw new ConcurrentModificationException();
      if (!hasNext())
        throw new NoSuchElementException();

      AnyType nextValue = current.getData();
      current = current.getNext();
      okToRemove = true;
      return nextValue;
    }

    public void remove()
    {
      if (modCount != expectedModCount)
        throw new ConcurrentModificationException();
      if (!okToRemove)
        throw new IllegalStateException();

      DoublyLinkedList.this.remove(current.getPrev());
      expectedModCount++;
      okToRemove = false;
    }
  }
}

