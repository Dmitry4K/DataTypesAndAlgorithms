import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class MergeSort {
    public static void main(String[] args) {
        assertSolution(new ArrayList<>(List.of(1, 2, 3)));
        assertSolution(new ArrayList<>(List.of(1)));
        assertSolution(new ArrayList<Integer>(List.of()));
        assertSolution(new ArrayList<>(List.of(3, 2, 1)));
        assertSolution(new ArrayList<>(List.of(6, 5, 4, 3, 2, 1)));
        assertSolution(new ArrayList<>(List.of(6, 4, 2, 5, 7, 1, 8, 3, 9)));
    }
    public static <T extends Comparable<T>> void assertSolution(List<T> list) {
        var insert = new ArrayList<>(List.copyOf(list));
        var expected = new ArrayList<>(List.copyOf(list));
        new MergeSort().sort(insert);
        Collections.sort(expected);

        assert insert.equals(expected);
    }
    public <T extends Comparable<T>> void sort(ArrayList<T> list) {
        sort(list, 0, list.size()-1);
    }

    private <T extends Comparable<T>> void sort(ArrayList<T> list, int l, int r) {
        if (r-l > 0) {
            int q = (l + r)/2;
            sort(list, l, q);
            sort(list, q + 1, r);
            merge(list, l, q, r);
        }
    }

    private <T extends Comparable<T>> void merge(ArrayList<T> list, int l, int q, int r) {
        var result = new ArrayList<T>(r - l + 1);
        int j = l, k = q + 1;
        for (;j < q + 1 && k < r + 1;) {
            if (list.get(j).compareTo(list.get(k)) < 0) {
                result.add(list.get(j));
                j++;
            } else {
                result.add(list.get(k));
                k++;
            }
        }
        for (; j < q + 1; j++) {
            result.add(list.get(j));
        }
        for (; k < r + 1; k++) {
            result.add(list.get(k));
        }
        for (int m = 0, n = l; m < result.size(); m++, n++) {
            list.set(n, result.get(m));
        }
    }
}
