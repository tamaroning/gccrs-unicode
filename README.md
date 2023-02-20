# THIS REPO IS AN EXPERIMENT FOR GCCRS TO SUPPRT UNICODE
Reach out to me (tamaroning) in gccrs Zulip chat!

# Build
```
git clone <THIS REPO>
cd gccrs-unicode
cmake -S . -B build
cmake --build build
```

# Run
```
./build/gccrs-unicode
```

This commands executes tokenizing a simple sequence of unicode identifiers below:

input (hardcoded in src/main.cc) : `"abc\nxyz\t\tあいうえお \r かきくけこ "`

output (stdout) :

```rust
Token {
        kind: 0
        pos: 0
        str: abc
}
Token {
        kind: 0
        pos: 4
        str: xyz
}
Token {
        kind: 0
        pos: 9
        str: あいうえお
}
Token {
        kind: 0
        pos: 27
        str: かきくけこ
}
```

# Details
Identifiers are compatible with identifiers defined in Rust Reference.

# TODO
- [ ] normalization of identifiers
- [ ] encoding to punycode

# References
- rustc, https://doc.rust-lang.org/stable/nightly-rustc/rustc_lexer/index.html
- unicode-xid, https://github.com/unicode-rs/unicode-xid/blob/master/src/tables.rs
- gccrs, https://github.com/Rust-GCC/gccrs
- my note, https://hackmd.io/9mElktLvRNqZsSpjr966_g
