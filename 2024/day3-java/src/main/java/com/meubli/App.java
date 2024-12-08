package com.meubli;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Hello world!
 */
public class App {
    public static void main(String[] args) throws IOException {
        String payload = Files.readString(Path.of("src/main/resources/input_2.txt"));
        System.out.println(partTwo(payload));
    }

    public static int partOne(String payload) {
        Pattern pattern = Pattern.compile("(mul\\()(\\d{1,3}),(\\d{1,3})\\)");

        Matcher matcher = pattern.matcher(payload);

        int total = 0;
        while (matcher.find()) {
            int nb1 = Integer.parseInt(matcher.group(2));
            int nb2 = Integer.parseInt(matcher.group(3));

            total += nb1 * nb2;
        }

        return total;
    }

    public static int partTwo(String payload) {
        Pattern pattern = Pattern.compile("(?<mul>(mul\\()(?<arg1>\\d{1,3}),(?<arg2>\\d{1,3})\\))|(?<dont>don't\\(\\))|(?<do>do\\(\\))");

        Matcher matcher = pattern.matcher(payload);

        boolean active = true;
        int total = 0;
        while (matcher.find()) {
            if (matcher.group("dont") != null) {
                active = false;
            } else if (matcher.group("do") != null) {
                active = true;
            } else if (matcher.group("mul") != null && active) {
                int nb1 = Integer.parseInt(matcher.group("arg1"));
                int nb2 = Integer.parseInt(matcher.group("arg2"));
                total += nb1 * nb2;
            }
        }
        return total;
    }
}
