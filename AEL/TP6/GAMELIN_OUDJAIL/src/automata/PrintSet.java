package automata;

import java.util.Collection;
import java.util.HashSet;

public class PrintSet<E> extends HashSet<E> {

	public PrintSet() {
	}

	public PrintSet(Collection<? extends E> c) {
		super(c);
	}

	public PrintSet(int initialCapacity) {
		super(initialCapacity);
	}

	public PrintSet(int initialCapacity, float loadFactor) {
		super(initialCapacity, loadFactor);
	}
	public String toString(){
		if (this.isEmpty())
			return "{}";
		StringBuffer buff = new StringBuffer();
		buff.append("{");
		for (E elt : this){
			buff.append(elt.toString());
			buff.append(',');
		}
		buff.deleteCharAt(buff.length()-1);
		buff.append("}");
		return buff.toString();		
	}

}
