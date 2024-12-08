fn main() {
    let lists = read_input("input_part2.txt");
    let result = part2(lists.0, lists.1);
    // afficher result avec println!
    println!("Result: {}", result);
}

fn part1(list1: Vec<u32>, list2: Vec<u32>) -> u32 {
    let mut result: u32 = 0;
    let mut list1_sorted = list1.to_vec();
    list1_sorted.sort();
    let mut list2_sorted = list2.to_vec();
    list2_sorted.sort();
    for (val1, val2) in list1_sorted.iter().zip(list2_sorted.iter()) {
        result += val1.abs_diff(*val2);
    }
    return result;
}

fn part2(list1: Vec<u32>, list2: Vec<u32>) -> u32 {
    let mut result: u32 = 0;
    // iterate over list2 and register the number of occurences of each value in a map
    let mut map = std::collections::HashMap::new();
    for val in list2 {
        *map.entry(val).or_insert(0) += 1;
    }
    for val in list1 {
        result += val * map.get(&val).unwrap_or(&0);
    }
    return result;
}

//This function reads the two lists from the input file
// data in the file has the form:
// 1   5
// 2   6
// 3   7
// 4   8
// 5   9
fn read_input(file_path: &str) -> (Vec<u32>, Vec<u32>) {
    // read data from the file
    let contents = std::fs::read_to_string(file_path).unwrap();
    // split the file contents into lines
    let lines: Vec<String> = contents.lines().map(|s| s.to_string()).collect();
    // put first number of each line in the first list, and the second number in the second list
    let mut list1: Vec<u32> = Vec::new();
    let mut list2: Vec<u32> = Vec::new();
    for line in lines {
        let split: Vec<u32> = line.split("   ").map(|s| s.parse().unwrap()).collect();
        list1.push(split[0]);
        list2.push(split[1]);
    }
    return (list1, list2);
}

// tests

#[cfg(test)]
mod tests {
    use crate::*;

    #[test]
    fn part2_1() {
        assert_eq!(part2(vec![1, 2, 3], vec![1, 2, 3]), 6);
    }

    #[test]
    fn part2_2() {
        let list1 = vec![3, 4, 2, 1, 3, 3];
        let list2 = vec![4, 3, 5, 3, 9, 3];
        assert_eq!(part2(list1, list2), 31);
    }
    #[test]
    fn part1_1() {
        let list1 = vec![2, 4, 3];
        let list2 = vec![2, 3, 1];
        assert_eq!(part1(list1, list2), 3);
    }
    #[test]
    fn part1_2() {
        let list1 = vec![1, 3, 2];
        let list2 = vec![2, 3, 1];
        assert_eq!(part1(list1, list2), 0);
    }
    #[test]
    fn part1_3() {
        let list1 = vec![3, 4, 2, 1, 3, 3];
        assert_eq!(part1(list1, list2), 11);
        let list2 = vec![4, 3, 5, 3, 9, 3];
    }

    #[test]
    fn read_input_test() {
        let (list1, list2) = crate::read_input("input_test.txt");
        assert_eq!(list1, vec![1, 2, 3, 4, 5]);
        assert_eq!(list2, vec![5, 6, 7, 8, 9]);
    }
}
