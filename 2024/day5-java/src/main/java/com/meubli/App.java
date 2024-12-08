package com.meubli;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Hello world!
 */
public class App {
    public static void main(String[] args) throws IOException {
        String payload = Files.readString(Path.of("src/main/resources/input_1.txt"));
        System.out.println(partOne(payload));
    }

    public static int partOne(String payload) {
        Map<Integer, List<Integer[]>> mapRules = new HashMap<>();

        String[] lines = payload.split("\n");

        Pattern patternRule = Pattern.compile("(\\d+)\\|(\\d+)");

        Pattern patternUpdate = Pattern.compile("\\d+,.*");
        for (String line : lines) {
            Matcher matcherRule = patternRule.matcher(line);
            if (matcherRule.matches()) {
                int a = Integer.parseInt(matcherRule.group(1));
                int b = Integer.parseInt(matcherRule.group(2));

                mapRules.computeIfAbsent(a, k -> new ArrayList<>()).add(new Integer[]{a, b});
            }

            Matcher matcherUpdate = patternUpdate.matcher(line);
            if (matcherUpdate.matches()) {
                String[] split = line.split(",");
                for (String s : split) {
                    if (mapRules.containsKey(Integer.parseInt(s))) {
                        return Integer.parseInt(s);
                    }
                }
            }
        }
        return 0;
    }

}
