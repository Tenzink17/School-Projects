package SparseVector;
import java.util.Iterator;

// an interface for abstraction and run time polymorphism

public interface List<AnyType>
{
  void clear();
  
  int size();

  boolean isEmpty();

  AnyType get(int index);

  AnyType set(int index, AnyType newValue);

  boolean add(AnyType newValue);

  void add(int index, AnyType newValue);

  AnyType remove(int index);

  Iterator<AnyType> iterator();
}
