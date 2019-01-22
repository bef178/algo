package any;

import java.util.AbstractMap.SimpleImmutableEntry;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Map.Entry;
import java.util.Queue;
import java.util.Set;

public class Topo<K extends Comparable<K>> {

    private class Node {

        K k;

        int indegree = 0;

        Set<Node> children = new HashSet<>();

        public Node(K k) {
            this.k = k;
        }

        @Override
        public boolean equals(Object o) {
            if (o == this) {
                return true;
            }
            if (o instanceof Topo.Node) {
                @SuppressWarnings("unchecked")
                Node another = (Node) o;
                return this.k.equals(another.k);
            }
            return false;
        }

        @Override
        public int hashCode() {
            return this.k.hashCode();
        }
    }

    public static void main(String[] args) {
        Topo<Integer> topo = new Topo<>();
        topo.add(1, 2, 3, 6);
        topo.add(1, 4, 5, 6);
        topo.add(4, 2);
        topo.add(5, 2);
        System.out.println(topo.toPartialSequence());
    }

    private Set<Entry<K, K>> edges = new HashSet<>();

    private HashMap<K, Node> nodes = new HashMap<>();

    @SuppressWarnings("unchecked")
    public void add(K... values) {
        for (int i = 1; i < values.length; i++) {
            edges.add(new SimpleImmutableEntry<K, K>(values[i - 1], values[i]));
        }
    }

    public void clear() {
        edges.clear();
    }

    public Queue<K> partialSort() {
        for (Entry<K, K> edge : edges) {
            if (!nodes.containsKey(edge.getKey())) {
                nodes.put(edge.getKey(), new Node(edge.getKey()));
            }
            Node from = nodes.get(edge.getKey());
            if (!nodes.containsKey(edge.getValue())) {
                nodes.put(edge.getValue(), new Node(edge.getValue()));
            }
            Node to = nodes.get(edge.getValue());
            from.children.add(to);
            to.indegree++;
        }

        Queue<Node> readys = new LinkedList<>();
        for (Node node : nodes.values()) {
            if (node.indegree == 0) {
                readys.add(node);
            }
        }

        Queue<K> result = new LinkedList<>();
        while (!readys.isEmpty()) {
            Node node = readys.remove();
            result.add(node.k);
            nodes.remove(node.k);
            for (Node child : node.children) {
                child.indegree--;
                if (child.indegree == 0) {
                    readys.add(child);
                }
            }
        }
        if (!nodes.isEmpty()) {
            throw new IllegalArgumentException();
        }

        nodes.clear();

        return result;
    }

    public CharSequence toPartialSequence() {
        Queue<K> values = partialSort();
        StringBuilder sb = new StringBuilder();
        for (K k : values) {
            sb.append(k.toString()).append(',');
        }
        sb.setLength(sb.length() - 1);
        return sb;
    }
}
