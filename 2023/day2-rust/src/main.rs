use std::{
    fs::File,
    io::BufRead,
    io::{self, BufReader},
    str::FromStr,
};

struct Set {
    pub r: u32,
    pub g: u32,
    pub b: u32,
}

impl Clone for Set {
    fn clone(&self) -> Set {
        Set {
            r: self.r,
            g: self.g,
            b: self.b,
        }
    }
}

#[derive(Debug, PartialEq, Eq)]
struct ParseSetError;
impl FromStr for Set {
    type Err = ParseSetError;
    fn from_str(line: &str) -> Result<Self, <Self as FromStr>::Err> {
        let splits = line.split(',');

        let mut r = 0;
        let mut g = 0;
        let mut b = 0;
        for split in splits {
            let mut digit_and_color = split.trim().split(' ');
            let digit = digit_and_color
                .next()
                .ok_or(ParseSetError)?
                .trim()
                .parse::<u32>()
                .map_err(|_| ParseSetError)?;

            let color = digit_and_color.next().ok_or(ParseSetError)?;

            if color == "green" {
                g = digit;
            }
            if color == "blue" {
                b = digit;
            }
            if color == "red" {
                r = digit;
            }
        }

        Ok(Set { r, g, b })
    }
}
struct Game {
    id: u32,
    sets: Vec<Set>,
}

#[derive(Debug, PartialEq, Eq)]
struct ParseGameError;

impl Game {
    pub fn id(&self) -> u32 {
        self.id
    }

    pub fn is_possible(&self, max_r: u32, max_g: u32, max_b: u32) -> bool {
        for set in &self.sets {
            if set.r > max_r || set.g > max_g || set.b > max_b {
                return false;
            }
        }

        true
    }

    pub fn power(&self) -> u32 {
        let mut max_r = 0;
        let mut max_g = 0;
        let mut max_b = 0;

        self.sets.iter().for_each(|set| {
            max_r = std::cmp::max(set.r, max_r);
            max_g = std::cmp::max(set.g, max_g);
            max_b = std::cmp::max(set.b, max_b);
        });
        max_r * max_b * max_g
    }
}
impl FromStr for Game {
    type Err = ParseGameError;
    fn from_str(line: &str) -> Result<Self, <Self as FromStr>::Err> {
        let mut l = line.to_string();
        // remove 'Game '
        l = l.get(5..l.len()).ok_or(ParseGameError)?.to_string();

        let mut split = l.split(':');

        let id = split
            .next()
            .ok_or(ParseGameError)?
            .parse::<u32>()
            .map_err(|_| ParseGameError)?;
        let body = split.next().ok_or(ParseGameError)?;

        let mut sets = Vec::new();

        for set_str in body.split(';') {
            sets.push(Set::from_str(set_str).map_err(|_| ParseGameError)?);
        }

        Ok(Game { id, sets })
    }
}

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let input = File::open("input.txt")?;

    let reader = BufReader::new(input);

    let max_r = 12;
    let max_g = 13;
    let max_b = 14;

    let mut sum_incorrect_ids = 0;
    let mut sum_powers = 0;

    let mut line_number = 0;
    for line_rslt in reader.lines() {
        line_number += 1;
        let line = line_rslt.unwrap();
        let game = Game::from_str(line.as_str())
            .expect(format!("failed to read line {}", line_number).as_str());

        if game.is_possible(max_r, max_g, max_b) {
            sum_incorrect_ids += game.id();
        }

        sum_powers += game.power();
    }

    println!("sum ids: {}", sum_incorrect_ids);

    println!("sum powers: {}", sum_powers);
    Ok(())
}
