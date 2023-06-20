import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class InsertSort {
    public static void main(String[] args) {
        assertSolution(new ArrayList<>(List.of(1, 2, 3)));
        assertSolution(new ArrayList<>(List.of(1)));
        assertSolution(new ArrayList<Integer>(List.of()));
        assertSolution(new ArrayList<>(List.of(3, 2, 1)));
        assertSolution(new ArrayList<>(List.of(6, 5, 4, 3, 2, 1)));
        assertSolution(new ArrayList<>(List.of(6, 4, 5, 7, 1, 8, 3, 9)));
    }
    public static <T extends Comparable<T>> void assertSolution(List<T> list) {
        var insert = new ArrayList<>(List.copyOf(list));
        var expected = new ArrayList<>(List.copyOf(list));
        new InsertSort().sort(insert);
        Collections.sort(expected);

        assert insert.equals(expected);
    }

    public <T extends Comparable<T>> void sort(List<T>  list) {
        for (int i = 1; i < list.size(); i++) {
            int j = i - 1;
            T cur = list.get(i);
            while (j >= 0 && cur.compareTo(list.get(j)) < 0) {
                list.set(j + 1, list.get(j));
                j--;
            }
            list.set(j + 1, cur);
        }
    }
}
