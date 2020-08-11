# OpenSSL

## [OpenSSL enc](https://wiki.openssl.org/index.php/Enc)
```
$ openssl enc -ciphername [options]

```

## Salts
Salt is random data that helps protect against dictionary and other precomputation attacks. Generally, salt is used in password-based 
systems and is concatenated to the front of a password before processing. Password systems often use a one-way hash function to turn 
a password into an “authenticator.” In the simplest such system, if there were no salt, an attacker could build a dictionary of 
common passwords and just look up the original password by authenticator.

## Initialization vectors [(IVs)](https://en.wikipedia.org/wiki/Initialization_vector)
The IV can’t be sequential; it must be random. One popular example in which a real IV is required for maximizing security is when using the CBC encryption mode

## Password [security](https://auth0.com/blog/hashing-in-action-understanding-bcrypt/)
Passwords should be stored using salted iterated hashes, using an algorithm such as PBKDF2, scrypt or bcrypt.
 - "Salting" involves adding a random string to each password and prevents use of precomputed "rainbow tables".
 - "Iterating" means performing the hash multiple times; this slows down bruteforce password guessing attacks. In combination these measures make it more difficult for an attacker to obtain user passwords if the database is compromised.
