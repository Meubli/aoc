use std::fs;

fn parse_map(input: &str) -> Vec<Vec<char>> {
    input.lines().map(|line| line.chars().collect()).collect()
}

fn find_numbers(map: &Vec<Vec<char>>) -> Vec<usize> {
    let mut numbers = Vec::new();

    for (i, row) in map.iter().enumerate() {
        let mut was_previous_char_number = false;
        let mut digits_index: Vec<usize> = vec![];
        for (j, &ch) in row.iter().enumerate() {
            if ch.is_digit(10) {
                was_previous_char_number = true;
                digits_index.push(j);
            } else {
                if was_previous_char_number {
                    if digits_index
                        .clone()
                        .into_iter()
                        .fold(false, |accumulator, current_value| {
                            accumulator || is_adjacent_to_symbol(i, current_value, map)
                        })
                    {
                        let mut number = 0;
                        for (index, character_index) in
                            digits_index.clone().into_iter().rev().enumerate()
                        {
                            number += usize::pow(10_usize, (index).try_into().unwrap())
                                * row[character_index].to_digit(10).unwrap() as usize;
                        }
                        numbers.push(number);
                    }
                }
                digits_index.clear();
                was_previous_char_number = false;
            }
        }
    }

    numbers
}

fn is_adjacent_to_symbol(i: usize, j: usize, map: &Vec<Vec<char>>) -> bool {
    let directions = [
        (0, 1),
        (0, -1),
        (1, 0),
        (-1, 0),
        (-1, -1),
        (1, 1),
        (-1, 1),
        (1, -1),
    ];

    for (dx, dy) in directions.iter() {
        let ni = i as i32 + dx;
        let nj = j as i32 + dy;

        if ni >= 0 && ni < map.len() as i32 && nj >= 0 && nj < map[i].len() as i32 {
            if map[ni as usize][nj as usize] != '.' && !map[ni as usize][nj as usize].is_digit(10) {
                return true;
            }
        }
    }

    false
}

fn main() {
    // let input = fs::read_to_string("input.txt").expect("failed to read input file");
    // let schematic = parse_map(&input);
    // let numbers = find_numbers(&schematic);

    // println!("{numbers:?}");
    // let sum: usize = numbers.iter().sum();
    // println!("Sum of part numbers: {}", sum);
    let map = include_bytes!("../input.txt");
    let width = map.iter().position(|b| b == &b'\n').unwrap() as isize;
    println!(
        "{}",
        (0..map.len() - 2)
            .filter(|i| {
                map[*i].is_ascii_digit()
                    && !map.get(i.wrapping_sub(1)).map_or(false, u8::is_ascii_digit)
            })
            .map(|i| {
                let d = (i + 1..i + 4)
                    .position(|i| !map[i].is_ascii_digit())
                    .unwrap()
                    + 1;
                (i, d as _, atoi::atoi::<usize>(&map[i..i + d]).unwrap())
            })
            .filter(|(i, d, _n)| {
                (-width - 2..-width + *d)
                    .chain([-1, *d])
                    .chain(width..width + *d + 2)
                    .any(|j| {
                        map.get((*i as isize + j) as usize)
                            .map_or(false, |b| b != &b'.' && b.is_ascii_punctuation())
                    })
            })
            .map(|(_i, _d, n)| n)
            .sum::<usize>()
    );
}
#[cfg(test)]
mod tests {
    use crate::find_numbers;
    use crate::is_adjacent_to_symbol;
    use crate::parse_map;
    #[test]
    fn test1() {
        let input = "467..114..\n...*......\n..35..633.\n......#...\n617*......\n.....+.58.\n..592.....\n......755.\n...$.*....\n.664.598..";
        let map = parse_map(input);
        let numbers = find_numbers(&map);

        let sum: usize = numbers.iter().sum();

        println!("{numbers:?}");
        assert_eq!(sum, 4361);
    }
    #[test]
    fn test2() {
        let input = "...................305.124................................432..............................................576..313.....514.................
.............113...-......&....................&...819...........654..../..........................&901................*....869.257.........
...377..&783../.................................9...........855*......940..463................-.........................844.*....@......679.";
        let map = parse_map(input);
        let numbers = find_numbers(&map);

        let sum: usize = numbers.iter().sum();

        println!("{numbers:?}");
        assert_eq!(sum, 6514);
    }

    #[test]
    fn is_adjacent_to_symbol_test3() {
        let input = "467..114..\n$.........";
        let map = parse_map(input);

        assert!(is_adjacent_to_symbol(0, 0, &map));
    }
    #[test]
    fn is_adjacent_to_symbol_test2() {
        let input = "467$.114..\n..........";
        let map = parse_map(input);

        assert!(is_adjacent_to_symbol(0, 2, &map));
    }
    #[test]
    fn is_adjacent_to_symbol_test4() {
        let input = "467..114..\n..........";
        let map = parse_map(input);

        assert!(!is_adjacent_to_symbol(0, 2, &map));
    }
    #[test]
    fn is_adjacent_to_symbol_test_side() {
        let input = "467....114\n..........";
        let map = parse_map(input);

        assert!(!is_adjacent_to_symbol(0, 9, &map));
    }
    #[test]
    fn is_adjacent_to_symbol_test_diagonal() {
        let input = "467..114..\n...*......";
        let map = parse_map(input);

        assert!(is_adjacent_to_symbol(0, 2, &map));
    }
}
