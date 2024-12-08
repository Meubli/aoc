package com.meubli;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

/**
 * Hello world!
 */
public class App {

    public final static Direction[] directions = {
            new Direction(0, -1, 0),
            new Direction(1, 0, 1),
            new Direction(0, 1, 2),
            new Direction(-1, 0, 3)
    };
    public static void main(String[] args) throws IOException {
        String payload = Files.readString(Path.of("src/main/resources/input.txt"));
        System.out.println(partTwo(payload));
    }



    public static int partTwo(String payload) {
        Position guardPosition = new Position(0, 0);
        Direction guardDirection = new Direction(0, -1, 0);
        Character[][] map = buildMap(payload, guardPosition);
        int total = 0;

        for (int i = 0; i< map.length; i++) {
            for (int j = 0; j < map[0].length; j++) {
                if (!map[i][j].equals('#')) {
                    map[i][j] = '#';
                    if (isLoop(map, guardPosition, guardDirection)) {
                        total++;
                    }
                    map[i][j] = '.';
                }
            }
        }

        return total;
    }


    public static boolean isLoop(Character[][] map, Position guardPositionInit, Direction guardDirectionInit) {
        List<Position> positionsHistory = new ArrayList<>();
        List<Direction> directionHistory = new ArrayList<>();
//        for (int i = 0; i < map.length; i++) {
//            for (int j = 0; j < map[0].length; j++) {
//                map[i][j] = mapInit[i][j];
//            }
//        }
//        System.out.println("new loop test");
        // Copy guard position
        Position guardPosition = new Position(guardPositionInit.x, guardPositionInit.y);
        Direction guardDirection = new Direction(guardDirectionInit.dx, guardDirectionInit.dy, guardDirectionInit.index);

        long inf_prot = 0;

        while (inf_prot < 100000000) {
            // print map
//            System.out.println("---------------");
//            for (Character[] characters : map) {
//                for (int j = 0; j < map[0].length; j++) {
//                    System.out.print(characters[j]);
//                }
//                System.out.println();
//            }
            Position nextPosition = new Position(guardPosition.x + guardDirection.dx, guardPosition.y + guardDirection.dy);
            if (nextPosition.x < 0 || nextPosition.x >= map[0].length || nextPosition.y < 0 || nextPosition.y >= map.length) {
                return false;
            }
            if (map[nextPosition.y][nextPosition.x] == '#') {
                guardDirection = directions[(guardDirection.index + 1)%4];
                nextPosition = new Position(guardPosition.x + guardDirection.dx, guardPosition.y + guardDirection.dy);
            }
//            map[guardPosition.y][guardPosition.x] = '.';
//            if (guardDirection.index == 0) {
//                map[nextPosition.y][nextPosition.x] = '^';
//            } else if (guardDirection.index == 1) {
//                map[nextPosition.y][nextPosition.x] = '>';
//            } else if (guardDirection.index == 2) {
//                map[nextPosition.y][nextPosition.x] = 'v';
//            } else if (guardDirection.index == 3) {
//                map[nextPosition.y][nextPosition.x] = '<';
//            }
            guardPosition = nextPosition;
            for (int i = 0; i < positionsHistory.size(); i++) {
                if (positionsHistory.get(i).equals(guardPosition) && directionHistory.get(i).equals(guardDirection)) {
                    return true;
                }
            }

            positionsHistory.add(guardPosition);
            directionHistory.add(guardDirection);
            inf_prot++;

        }
        return false;
    }
    /**
     * returns a matrix of characters
     * @param content
     * @return
     */
    private static Character[][] buildMap(String content, Position guardPosition) {
        String[] lines = content.split("\n");
        Character[][] map = new Character[lines.length][lines[0].length()];
        for (int i = 0; i < lines.length; i++) {
            for (int j = 0; j < lines[i].length(); j++) {
                map[i][j] = lines[i].charAt(j);
                if (map[i][j] == '^') {
                    guardPosition.x = j;
                    guardPosition.y = i;
                }
            }
        }
        return map;
    }
    public static class Position {
        public int x;
        public int y;

        public Position(int x, int y) {
            this.x = x;
            this.y = y;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (!(o instanceof Position position)) return false;
            return x == position.x && y == position.y;
        }

        @Override
        public int hashCode() {
            return Objects.hash(x, y);
        }

        @Override
        public String toString() {
            return "Position{" +
                    "x=" + x +
                    ", y=" + y +
                    '}';
        }
    }
    public static class Direction {
        public int dx;
        public int dy;
        public int index;

        public Direction(int dx, int dy, int index) {
            this.dx = dx;
            this.dy = dy;
            this.index = index;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (!(o instanceof Direction direction)) return false;
            return dx == direction.dx && dy == direction.dy && index == direction.index;
        }

        @Override
        public int hashCode() {
            return Objects.hash(dx, dy, index);
        }

        @Override
        public String toString() {
            return "Direction{" +
                    "dx=" + dx +
                    ", dy=" + dy +
                    ", index=" + index +
                    '}';
        }
    }
}
