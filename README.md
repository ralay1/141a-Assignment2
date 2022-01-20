# WI22-Assignment2
Design, test, and build our own Buffer Manager class
#### Due Jan 26, 11:30pm (PST)

## Introduction

This assignment has three parts:

1. First, you're going to implement your own version of a `Buffer Manager` class. 
2. Second, you're going to implement tests to ensure that your class works correctly -- then check it into git. 
3. The third part of this assignment is a "code review" -- where each student will code-review another student's work.

## Welcome to JobCo!

You've just started a new internship at JobCo, a chic software company in the heart of Silicon Valley that sells party balloons with integrated block-chain tracking. You've met your new manager, Chloe, who introduces you to the rest of the team. As you are wisked through the office, you race past a herd of zombies that are wandering aimlessly in the break room. "Oh my goodness", you say, in disbelief.  "Don't let them bother you", Chloe says smiling, "that's just the marketing department taking a lunch break". JobCo is going to be very interesting.

### Your FIRST Sprint Meeting

The next morning you get to sit in on your very first "Sprint Meeting" where the team discusses the work they're going to accomplish for the week. Each of the engineers talks briefly about their challenges and expected output. At last, all eyes drop onto you. Before panic seizes you, Chloes says, "Hey everyone, this is our new summer intern!". The team smiles knowingly, fully expecting you to soon become lunch for the Marketing department.  What happens next is mostly a blur. For one, you don't remember actually saying anything. But suddenly you realize that Chloe has tasked you with delivering some mission critical code, and FAST!  

### Your Team Makes a Decision

Just before the end of the standup meeting, Morris (a performance engineer) raises the topic of how slowly the application is performing. "Seriously", he says, "the app is running 5x slower today than it was a month ago". "What we need", he continues, "is someone to rewrite our string class to stop all the unnecessary memory allocations and performance problems."

Never one to miss an opportunity, Chloe exclaimed, "Great -- our new intern can build us a new string class this Sprint!". Sade, a Rady School student and UX designer on the team, says, "Hold on, why can't we just use the std::string class provided by the STL? Won't that be cheaper than building our own?"  Morris can barely contain himeself. "No!", he chides, "the STL is great in general, but it's way too big, and I just know we can build something smaller and faster!"

Sadly, no amount of arguing about re-inventing the wheel (or adhering to the DRY principle) would stop Morris and Chloe from building their own string class. Welcome to Silicon Valley. :)

## Assignment Details

Over this week's and next week's assignments, you are going to build a string class using an "aspect-oriented" design technique.  Instead of building one (large) class, you're going to assemble your `String` class from several smaller, "special-purpose" classes:

```
class BufferManager;  //your base class
class Searchable;  //a trait class meant to be "mixed-in" to other classes
class Sortable;    //another trait class
```

In this assignment, you are going to build the base class: `BufferManager` that will be used in next week's assignment.

---

### Part 1. -- Build your BufferManager<> template class

The `BufferManager` template class will be used in your upcoming `String` class assignment.  Since this class is a template, the entire implementation will exist inside the BufferManager.hpp file. There is no BufferManager.cpp file.  

> Prior experience says that if you get this right, most of next week's assignment is relatively easy. If you get this wrong, most of the rest of your implementation will not work.

The job of this class is to allocate, manage, and (eventually) delete the underying heap-buffer that any class that inherits from this class uses to hold information of a specific data type. In particular, this class will:

1. Allocate a heap memory buffer to contain your string data (chars)
2. Guarantee that the character buffer is always terminated with a null
3. Always tracks the current length of the string
4. Automatically and correctly grow/shrink the heap-buffer when your user changes the string 
5. Automatically delete the underlying heap-buffer when the `String` object is destroyed. Consider using `std::unique_ptr<>`. 

The BufferManager class wants to be as efficient as possible. As the user changes the string, this class should grow/shrink the underlying buffer in an time/space efficient way as possible.  We discussed this challenge in lecture, so refer to our discussion on this topic.

The overall performance the `BufferManager` class achieves will impact your grade.  So think about time/space efficiency. It's not hard if you're paying attention to when and how you allocate/reallocate/copy your internal buffer. 

In your starter project, you'll see we already created a (mostly) empty `BufferManager<>` class. You'll also notice we didn't provide any guidance on which methods you need to implement to make this class work. That decision is up to you. But we can tell you the scenarios you need to be able to handle:

#### Scenario 1 -- Construction

When someone makes a new `String`, it is empty by default. Empty strings should occupy no space. Typically, the buffer pointer that the `BufferManager` uses to manage the buffer is null at this point.  

```
String theString; //an empty string with length 0
```

#### Scenario 2 -- Assignment/Copy construction

It is possible to create a `String` class, and give it a non-null initializer value in the constructor:

```
String theString("hello world"); //this string requires buffer memory right from the start
```

In this scenario, the `BufferManager` needs to pre-allocate space on the heap for the buffer that will hold the contents of the `String`. Again, since time/space efficiency is important, you should think carefully about how large your buffer should be. 

1. Should it be exactly as large as the initialize string (+1 for the null terminator?)
2. Should be somewhat larger, so the string could grow "a little" without having to resize your buffer

> We refer to these choices as, "policy decisions". It is possible to write our code so that policies can be determined using class composition. This allows our user to influence how our class should behave (thus, policy).

#### Scenario 3 -- Mutating (add/insert/delete) some/all of your string

In this scenario, the user is using part of the mutatation API to add/delete/insert characters into an existing string. This can change the size requirements of the underlying buffer. 

```
String theString("hello world"); //string length is 11 (+1 for null terminator)
theString.append(" it's a really fine day in San Diego!"); //we just added nearly 40 characters to the string; resize buffer?
```

It's likely that your buffer will need to be resized at this point. We discussed the implications of that process in lecture. If the length of your current buffer + the length of the appended string is more than your current buffer can hold, you'll do something like this:

1. allocate a new buffer, big enough to hold original string + new string + null terminator
2. copy the contents of the old buffer to the new buffer
3. copy the content being "appended" to the end of the new buffer
4. delete the original buffer
5. set your internal buffer pointer to your buffer

> NOTE: The need to expand/grow your buffer can happen in a few ways. Someone might want to "append" characters to a `String`, which will cause the buffer to grow, and new characters appended. A different behavior might occur if someone tries to "insert" characters into an existing string. While the buffer may still expand, the underlying data in the buffer may be _logically_ split. Characters before the insertion point will remain unchanged. New characters will be inserted at the insertion point. And finally, characters after the insertion point may be shifted to the right.  A similar set of operations may occur if someone chooses to delete a span of characters in the middle of a `String`.  How can your `BufferManager` make these operations easier for the `String` class?

---

### Part 5. -- Testing your Buffer Manager class implementation 

See? Building a basic buffer manager class isn't all that hard. But making it run fast, and ensuring that uses memory efficiently takes considerably more effort. Finding the right balance between memory usage and performance can be a challenge.  In order to test your memory utilization and performance, you must write your own tests. 

> Although building the `String` class doesn't need to happen until next week, you might consider starting one now, to give yourself a way to test your `BufferManager` class more easily. It's up to you, as it's not required this week.

Still - no self-respecting engineer would consider the job done unless they had also provided a complete set of tests to ensure that the solution worked as designed. Well, we've already provided a basic testing harness for you, contained in the Testable.hpp file. 

> It is up to you to fully implement the tests for the `Buffer Manager` class. We have provided a copy of the simple, `Testable` class for this purpose. You might also consider using the excellent and widely used google testing framework (gtest). 


## Grading

Your submission will be graded along four dimensions:

```
Compile test: 20pts
OCF test:   20pts
Expand test:  20pts
Compact test:  20pts
Manual code review: 20pts
```

As we explained earlier, in addition to passing the basic tests, your code will be measured for memory efficiency and performance. Next week, our grading test harness will generate 1000's of strings and measure your memory usage and performance. So make sure you test performance and memory efficiency carefully.


## Code Style Guide

This isn’t your first class on software or programming, and you’re probably wondering how we expect your code to be structured and formatted.  From the perspective of our auto-grader, structure and format are completely irrelevant. However, your instructors also will be viewing your code as well, so you would be wise to adhere to a few rules of thumb. 

### Format and Clarity

Your code should be formatted to be easily readable by anyone with more than 1 year of programming experience.  Here are some guidelines for things that matter:

- Avoid dense and complicated code
- Be consistent!  Choose a coding standard for yourself and stick with it
- Partition your logic into class methods as needed to maintain clarity
- Document your code with comments that clearly indicate what you’re doing at a high level

## Submitting Your Work - Due Jan 26th at 11:30p (PST)

You’ll recall that your work is due by 11:30pm (PST).  We strongly recommend that you aim for 6p (PST) as to avoid the last minute mishaps that frequently occur when panic related to an impending deliverable begins, and we all tend to make silly mistakes.  

As we’ve said in lecture, you will turn your work in using GitHub. GitHub is an online code repository.  Managing code can be very confusing, but GitHub makes the process fairly easy. And the way we’re going to handle code in this class is even simpler still.  More on that later.

With that said, please understand that when you submit your work via GitHub, your changes are automatically timestamped. Meta data in the code repository makes it plainly obvious to humans and computers alike when your submission arrived.  This is worth mentioning, because the github timestamps on your submissions will be used to to arbitrate whether you turned your work in on time or not. 

Your homework will usually be auto-graded by “Vlad the Compiler” — otherwise known as our software-based auto-grader.  Vlad can be a bit harsh when it comes to scoring homework (see the syllabus), but he does have a somewhat casual relationship with deadlines.  During Grad-school, Vlad often spent spring-break in Cabo-San-Lucas where he learned to enjoy siestas.  Most nights, Vlad awakens from his last-afternoon siesta around midnight, to begin the process of grading your assignments. In other words, you can generally count on a 30 minute grace period for turning in your work. We strongly suggest that you do not try his patience.

**NOTE**: Please don't submit object or executable files with your submissions. Only check in text files (source, make, student.json, and so forth).  

Please make sure that you fill out your student.json file. We need your name, PID, email and the operating system you used for your work. For the operating system attribute, please specify "windows", "mac" or "linux". 

```
{
  "name"  : "Your Name",
  "pid"   : "Your StudentId",
  "email" : "Your Email",
  "os"    : "windows|mac|linux",
  "effort": "# of hours you spent on this assignment",
  "course": "ece141a"
}
```

### Getting Help

You can talk with your peers about this problem. You can ask your instructors about this too. But you cannot use any other code for reference in solving these problems. If you're really stuck with an algorithm, join us in the programming dojo to get unblocked. It's really essential that you think about this challenge and work to solve it yourself.
