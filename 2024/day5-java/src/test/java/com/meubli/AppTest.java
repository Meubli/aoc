package com.meubli;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.Test;

/**
 * Unit test for simple App.
 */
public class AppTest {

    @Test
    void partOne() {
        String data =   "MMMSXXMASM\n" +
                        "MSAMXMSMSA\n" +
                        "AMXSXMAAMM\n" +
                        "MSAMASMSMX\n" +
                        "XMASAMXAMM\n" +
                        "XXAMMXXAMA\n" +
                        "SMSMSASXSS\n" +
                        "SAXAMASAAA\n" +
                        "MAMMMXMMMM\n" +
                        "MXMXAXMASX";
        assertEquals(App.partOne(data), 18);
    }

    @Test
    void partTwo() {
        String data =   "MMMSXXMASM\n" +
                "MSAMXMSMSA\n" +
                "AMXSXMAAMM\n" +
                "MSAMASMSMX\n" +
                "XMASAMXAMM\n" +
                "XXAMMXXAMA\n" +
                "SMSMSASXSS\n" +
                "SAXAMASAAA\n" +
                "MAMMMXMMMM\n" +
                "MXMXAXMASX";
        assertEquals(App.partTwo(data), 9);
    }
}
