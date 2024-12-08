package com.meubli;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

/**
 * Hello world!
 */
public class App {
    public static void main(String[] args) throws IOException {
        String payload = Files.readString(Path.of("src/main/resources/input_2.txt"));
        System.out.println(partTwo(payload));
    }

    public static int partTwo(String payload) {
        MapInfo mapInfo = getMapInfo(payload);

        int total = 0;
        for (int y = 0; y < mapInfo.height(); y++) {
            for (int x = 0; x < mapInfo.width(); x++) {
                total += countMASAtPosition(mapInfo.map(), x, y, mapInfo.width(), mapInfo.height());
            }
        }

        return total;
    }

    public static int partOne(String payload) {
        MapInfo mapInfo = getMapInfo(payload);
        int[][] directions = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 }, { 1, 1 }, { -1, -1 }, { 1, -1 }, { -1, 1 } };

        int total = 0;
        for (int y = 0; y < mapInfo.height(); y++) {
            for (int x = 0; x < mapInfo.width(); x++) {
                if (mapInfo.map()[y][x].equals('X')) {
                    for (int[] direction : directions) {
                        if (searchDirectionPart1(mapInfo.map(), x, y, direction[0], direction[1], mapInfo.width(), mapInfo.height())) {
                            total ++;
                        }
                    }
                }

            }
        }

        return total;
    }

    private static MapInfo getMapInfo(String payload) {
        String[] lines = payload.split("\n");
        int width = lines[0].length();
        int height = lines.length;
        Character[][] map = new Character[height][width];
        for (int l = 0; l < height; l++) {
            String line = lines[l];
            for (int i = 0; i < width; i++) {
                map[l][i] = line.charAt(i);
            }
        }
        MapInfo mapInfo = new MapInfo(width, height, map);
        return mapInfo;
    }

    private record MapInfo(int width, int height, Character[][] map) {
    }

    public static boolean searchDirectionPart1(Character[][] map, int x, int y, int dx, int dy, int width, int height) {
        Character[] xmas = { 'X', 'M', 'A', 'S'};

        for (int i = 0; i < xmas.length; i++) {
            if (x + dx * i < 0 || x + dx * i >= width || y + dy * i < 0 || y + dy * i >= height) {
                return false;
            }
            if (!map[y + dy * i][x + dx * i].equals(xmas[i])) {
                return false;
            }
        }

        return true;
    }

    public static int countMASAtPosition(Character[][] map, int x, int y, int width, int height) {

        if (!map[y][x].equals('A')) {
            return 0;
        }
        if (y == 0 || y == height - 1 || x == 0 || x == width - 1) {
            return 0;
        }

        Character[][] combinaisons = {
                {'M', 'S', 'M', 'S'},
                {'M', 'S', 'S', 'M'},
                {'S', 'M', 'M', 'S'},
                {'S', 'M', 'S', 'M'},
        };

        int total = 0;

        for (Character[] combinaison : combinaisons) {
            if (map[y-1][x-1].equals(combinaison[0]) && map[y+1][x+1].equals(combinaison[1])) {
                if (map[y-1][x+1].equals(combinaison[2]) && map[y+1][x-1].equals(combinaison[3])) {
                    total++;
                }
            }
        }

        return total;
    }
}
