use fibonacci::Fibonacci;

/// Each new term in the Fibonacci sequence is generated by adding the
/// previous two terms. By starting with 1 and 2, the first 10 terms will
/// be: 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, ...
///
/// By considering the terms in the Fibonacci sequence whose values do not
/// exceed four million, find the sum of the even-valued terms.
pub fn solve() {
    let fib = Fibonacci::new(1u32, 2u32, 4*1000*1000_u32);
    let result = fib.fold(
        0_u32, |acc, n| {if n%2 == 0 { return acc+n }; acc },
    );
    println!("sum of even-valued terms in the fibonacci sequence {}", result);
}

