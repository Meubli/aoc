use std::{
    fs::{self, File},
    io::prelude::BufRead,
    io::BufReader,
};

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let input = File::open("input.txt")?;

    let reader = BufReader::new(input);

    let mut total_calibration = 0;
    let mut total_calibration_part2 = 0;
    for line_rslt in reader.lines() {
        let line = line_rslt.unwrap();
        total_calibration += line_calibration(line.clone().as_ref());
        total_calibration_part2 += line_calibration_part2(line.clone().as_ref());
    }

    println!("total calibration: {}", total_calibration);
    println!("total calibration part 2: {}", total_calibration_part2);
    Ok(())
}

struct Map {
    pub str: String,
    pub value: u32,
}

fn line_calibration_part2(line: &str) -> u32 {
    let map_digits: Vec<Map> = vec![
        Map {
            str: "one".to_string(),
            value: 1,
        },
        Map {
            str: "two".to_string(),
            value: 2,
        },
        Map {
            str: "three".to_string(),
            value: 3,
        },
        Map {
            str: "four".to_string(),
            value: 4,
        },
        Map {
            str: "five".to_string(),
            value: 5,
        },
        Map {
            str: "six".to_string(),
            value: 6,
        },
        Map {
            str: "seven".to_string(),
            value: 7,
        },
        Map {
            str: "eight".to_string(),
            value: 8,
        },
        Map {
            str: "nine".to_string(),
            value: 9,
        },
    ];

    // finding first digit.
    let mut first_digit = 0;
    let mut second_digit = 0;
    let mut tmp_str = String::from("");
    let mut should_break_loop = false;

    for character in line.chars() {
        match character.to_digit(10) {
            Some(digit) => {
                first_digit = digit;
                should_break_loop = true;
            }
            _ => {
                tmp_str.push(character);

                map_digits.iter().for_each(|m| {
                    if tmp_str.len() >= m.str.len() && tmp_str.contains(&m.str) {
                        first_digit = m.value;
                        should_break_loop = true;
                    }
                })
            }
        }

        if should_break_loop {
            break;
        }
    }

    tmp_str = String::from("");
    should_break_loop = false;

    for character in line.chars().rev() {
        match character.to_digit(10) {
            Some(digit) => {
                second_digit = digit;
                should_break_loop = true;
            }
            _ => {
                tmp_str.insert(0, character);

                map_digits.iter().for_each(|m| {
                    if tmp_str.contains(&m.str) {
                        second_digit = m.value;
                        should_break_loop = true;
                    }
                })
            }
        }

        if should_break_loop {
            break;
        }
    }

    return first_digit * 10 + second_digit;
}

fn line_calibration(line: &str) -> u32 {
    let first_digit = line.chars().into_iter().find_map(|c| c.to_digit(10));
    let second_digit = line.chars().rev().find_map(|c| c.to_digit(10));

    return first_digit.unwrap_or(0) * 10 + second_digit.unwrap_or(0);
}

#[cfg(test)]
mod tests {
    use crate::{line_calibration, line_calibration_part2};

    #[test]
    fn test_line_calibration_part_two_1() {
        let line = "two1nine";

        let line_calibration = line_calibration_part2(line);

        assert_eq!(29, line_calibration);
    }

    #[test]
    fn test_line_calibration_part_two_2() {
        let line = "eightwothree";

        let line_calibration = line_calibration_part2(line);

        assert_eq!(83, line_calibration);
    }
    #[test]
    fn test_line_calibration_part_two_3() {
        let line = "abcone2threexyz";

        let line_calibration = line_calibration_part2(line);

        assert_eq!(13, line_calibration);
    }

    #[test]
    fn test_line_calibration_1() {
        let line = "pqr3stu8vwx";

        let line_calibration = line_calibration(line);

        assert_eq!(38, line_calibration);
    }

    #[test]
    fn test_line_calibration_2() {
        let line = "1abc2";

        let line_calibration = line_calibration(line);

        assert_eq!(12, line_calibration);
    }
    #[test]
    fn test_line_calibration_3() {
        let line = "a1b2c3d4e5f";

        let line_calibration = line_calibration(line);

        assert_eq!(15, line_calibration);
    }

    #[test]
    fn test_line_calibration_4() {
        let line = "treb7uchet";

        let line_calibration = line_calibration(line);

        assert_eq!(77, line_calibration);
    }
}
