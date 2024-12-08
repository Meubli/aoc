fn main() {
    let lists = read_input_file("input.txt");
    println!("{} rules are safe.", part_2(lists));
}

fn part_1(lists: Vec<Vec<u32>>) -> u32 {
    let mut total_safe = 0;
    for list in lists.iter() {
        let is_safe_tuple = is_list_safe(list);
        match is_safe_tuple.0 {
            true => {
                total_safe += 1;
            }
            false => (),
        }
    }
    return total_safe;
}

fn part_2(lists: Vec<Vec<u32>>) -> u32 {
    let mut total_safe = 0;
    for list in lists.iter() {
        let is_safe_tuple = is_list_safe(list);
        if is_safe_tuple.0 {
            total_safe += 1;
        } else {
            for index in 0..list.len() {
                if is_list_safe(&exclure_index(list, index)).0 {
                    total_safe += 1;
                    break;
                }
            }
        }
    }
    return total_safe;
}

fn exclure_index<T: Clone>(vec: &[T], index: usize) -> Vec<T> {
    let avant = &vec[..index]; // Slice avant l'élément à exclure
    let apres = &vec[index + 1..]; // Slice après l'élément à exclure

    // Combine les deux slices
    avant.iter().chain(apres.iter()).cloned().collect()
}

fn is_list_safe(list: &Vec<u32>) -> (bool, usize) {
    let mut is_increasing = false;
    let mut first_tuple = true;
    for i in 0..list.len() - 1 {
        if first_tuple {
            if list[i] > list[i + 1] {
                is_increasing = false;
                first_tuple = false;
            } else if list[i] < list[i + 1] {
                is_increasing = true;
                first_tuple = false;
            }
        }
        if (is_increasing && list[i] > list[i + 1])
            || (!is_increasing && list[i] < list[i + 1])
            || (list[i].abs_diff(list[i + 1]) > 3)
            || (list[i] == list[i + 1])
        {
            return (false, i);
        }
    }
    (true, 0)
}

// this method read the input file and returns a list of lists. one list per line.
// data has the format:
// 1 2 3
// 3 2 1
fn read_input_file(file_path: &str) -> Vec<Vec<u32>> {
    let contents =
        std::fs::read_to_string(file_path).expect("Something went wrong reading the file");

    let lines: Vec<String> = contents.lines().map(|s| s.to_string()).collect();

    //parse lists from lines
    let lists: Vec<Vec<u32>> = lines
        .iter()
        .map(|line| {
            line.split(' ')
                .map(|substring| substring.parse::<u32>().unwrap())
                .collect()
        })
        .collect();
    return lists;
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_read_input_file() {
        let lists = read_input_file("input_test.txt");
        assert_eq!(lists.len(), 2);
        vec![3, 2, 1]
            .iter()
            .zip(lists[1].iter())
            .for_each(|(a, b)| assert_eq!(a, b));
        vec![1, 2, 3]
            .iter()
            .zip(lists[0].iter())
            .for_each(|(a, b)| assert_eq!(a, b));
    }
    #[test]
    fn test_part_1() {
        let lists = read_input_file("input_test.txt");
        assert_eq!(part_1(lists), 2);
    }
    #[test]
    fn test_part_1_2() {
        let lists = read_input_file("input_test2.txt");
        assert_eq!(part_1(lists), 2);
    }
    #[test]
    fn test_part_2_1() {
        let lists = read_input_file("input_test2.txt");
        assert_eq!(part_2(lists), 4);
    }
}
