package com.meubli;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.Test;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

/**
 * Unit test.txt for simple App.
 */
public class AppTest {

    @Test
    void partTwo() throws IOException {
        String data =   Files.readString(Path.of("src/test/resources/example.txt"));
        assertEquals(6, App.partTwo(data));
    }

    @Test
    void partTwo2() throws IOException {
        String data =   Files.readString(Path.of("src/test/resources/test.txt"));
        assertEquals(2, App.partTwo(data));
    }
}
