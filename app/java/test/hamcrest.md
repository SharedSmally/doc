# Hamcrest
A framework for writing matcher objects allowing ‘match’ rules to be defined declaratively. 

Hamcrest comes with a library of useful matchers:

## Core
- anything - always matches, useful if you don’t care what the object under test is
- describedAs - decorator to adding custom failure description
- is - decorator to improve readability

## Logical
- allOf - matches if all matchers match, short circuits (like Java &&)
- anyOf - matches if any matchers match, short circuits (like Java ||)
- not - matches if the wrapped matcher doesn’t match and vice versa Object
- equalTo - test object equality using Object.equals
- hasToString - test Object.toString
- instanceOf, isCompatibleType - test type
- notNullValue, nullValue - test for null
- sameInstance - test object identity

##Beans
- hasProperty - test JavaBeans properties

## Collections
- array - test an array’s elements against an array of matchers
- hasEntry, hasKey, hasValue - test a map contains an entry, key or value
- hasItem, hasItems - test a collection contains elements
- hasItemInArray - test an array contains an element

## Number
- closeTo - test floating point values are close to a given value
- greaterThan, greaterThanOrEqualTo, lessThan, lessThanOrEqualTo - test ordering

## Text
- equalToIgnoringCase - test string equality ignoring case
- equalToIgnoringWhiteSpace - test string equality ignoring differences in runs of whitespace
- containsString, endsWith, startsWith - test string matching

## Sugar

Hamcrest strives to make tests as readable as possible. For example, the is matcher is a wrapper that doesn’t add any extra behavior to the underlying matcher. The following assertions are all equivalent:
```
assertThat(theBiscuit, equalTo(myBiscuit)); 
assertThat(theBiscuit, is(equalTo(myBiscuit))); 
assertThat(theBiscuit, is(myBiscuit));
```
The last form is allowed since is(T value) is overloaded to return is(equalTo(value)).
