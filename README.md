# The Networking Bracelet

The idea of the Networking Bracelet is to encourage and facilitate interesting, spontaneous in-person
conversations with the most interesting people at networking events of various kinds.

Simply mark people as people of interest from an app or website in a networking event and get notified by 
vibration and matching light patterns on bracelets every time a mutual interest is encountered.

## Prototype

This repository contains the code for the rudimentary two-bracelet interaction demo made with Arduino Micros, 
HC-05 Bluetooth modules and WS2812B LED strips for the ELEC-9801 Design Thinking and Electronic Prototyping
course. NB_central_BLE and NB_peripheral_IoT are incomplete remnants of our initial approach involving Arduino
Nano 33 BLEs but due to their incompatibility with the FastLED library, an alternate approach was adopted using
te abovementioned components. This can be found in the NB_micro_HC05 folder. Neither approach is even close to
what the eventual, finished product would be like as both only support two bracelets, whereas a ready system
would have to scale potentially to thousands of bracelets along with communicating with a smartphone, where
mathcmaking software would be running.

The final, simple two-bracelet prototype demonstrating a typical user interaction works by two
Arduino Micros controlling one HC-05 and WS2812B LED strip each, where the HC-05
Bluetooth modules are configured as a master and a slave such that the master always
looks for and connects to the slave when it is discoverable. Once a Bluetooth connection has
been established, both continuously broadcast their IDs to each other approximately every
~20ms and if they correspond to the matchIDs that stores each bracelet’s matches, a unique
light pattern is created for the particular match by using the IDs of the bracelets as seeds for
random integer generators, which generate two random hues at constant brightness and
saturation. An average of these is taken for a blending color and all three are displayed on
both bracelets while they remain connected.

Once either or both bracelets are turned off, no colors are displayed until they are again
paired, which can take quite a long time from 7 to 20 seconds due to the limitations of the
HC-05 modules. To see what matches with different IDs would like like, i.e. to alter the color
pattern, or to verify that no false matches are produced, the slave can be connected to via a
Bluetooth serial application such as Serial Bluetooth Terminal, while the master is off and
its ID can be changed by sending it the “@ID” command, where “@” signifies a command to change 
the ID and “ID” is a 32bit integer (123, 456, 789, 111, 222, 333 for matches).

## Demo

The demo video can be viewed at: [https://www.youtube.com/watch?v=1mS3KUr62uY](https://www.youtube.com/watch?v=1mS3KUr62uY).

## Design Proposal / Pitch for final product

### Introduction

Networking event organizers – our potential clients – are on the right track to their goal of facilitating
connections between people with the idea of inviting them to gather at an attractive venue with an
interesting programme. However, this alone is not sufficient for building meaningful, productive and
lasting relationships [1]. This has led to the adoption of professional matchmaking software, which
connects similar people but also overloads the attendees’ – our users’ – calendars with meetings,
impairing their experience of the event with a sense of urgency and stress. Furthermore, people new
to the event, location or industry may be overwhelmed by the number of people and activities, thus
missing the most interesting people to them, especially if they are introverted.

Our solution, descriptively called the Networking Bracelet, aims to improve the attendees’
experience and, consequently, help networking event organizers to make their events more effective
and appealing for their guests by encouraging and facilitating interesting, spontaneous in-person
conversations between people most interested in each other. With the networking bracelets,
attendees of events can mark others as people of interest from an app based on their characteristics
such as demographics, professional role, and interests and get notified by vibration and matching
light patterns on both of their bracelets every time mutually interested people find themselves at
proximity. This helps new attendees to spontaneously discover contacts of interest, nudges introverts
to start conversations and provides a great excuse for people stuck in conversations to switch if
another interesting person walks by, improving the event.

### Extended definition:

The Networking Bracelet is an electronic wristband that notifies its wearer about interesting people
nearby via vibration and matching light patterns. It connects to an app on its wearer’s phone that
algorithmically matches the wearer with other people based on shared interests and complementing
characteristics and uploads the matching persons’ IDs to the bracelet. It then compares these to its
own with other nearby bracelets over the Bluetooth® Low Energy wireless communication protocol
[2] and if a match is found, alerts the user via vibration created by an actuator and light patterns
produced with independently controlled RGB LEDs (light-emitting diodes capable of producing
combinations of red, green and blue light) that are synchronized with the identical hardware of a
matching bracelet to make the match visible to both parties.

The Networking Bracelet is meant to be used in a wide variety of events, where networking is the
main purpose. These include various conferences, expos, seminars, summits and conventions where
the event organizers want to facilitate the networking of their attendees’, who can range from
businesspeople and legislators to researchers, creative professionals and many others. The use of
Networking Bracelets signals this intent and helps create various new kinds of professional
relationships, collaborations and friendships that might otherwise go unformed due to, for example,
isolation of professional groups, well-established comfort zones of regular attendees, introversion
and overwhelming opportunity for newcomers, all of which have been listed as major problems by
our potential users [3]. Revitalized, organic cross-group intermingling may result in surprising
collaborations, deeper multidisciplinary industry connections within and across firms and productive
new ideas and perspectives.

For example, a final year biology student may mention their thesis about biomaterials in regenerative
medicine on their profile, which leads to a match with an industry veteran mechanical engineer with
interest in nanotechnology. They might strike up a conversation about the exquisite greenery of the
venue, that eventually leads them down a path to commercially replicating photosynthesis in
synthetic materials. The power of spontaneous, casual, and exploratory conversation with no agenda
must not be underestimated when it comes to relationship building.

### Conclusion

In an era where networking is more important than ever, it is also more demanding. One may often
find themselves in entirely new, unfamiliar environments with overwhelming possibilities in terms of
people to meet, conversations to be had and connections to be established and might face
difficulties with starting conversations as an introvert or ending them as an extrovert, therefore
failing to find the people most interesting to them. The Networking Bracelet, entirely unique in its
application, is the solution that best combines excitement and utility in in-person networking by
encouraging spontaneous conversations, resulting in deep, genuine relationships between the
people that most want to connect with each other. It helps people to find each other and lowers the
barrier of starting conversations between them while enhancing the event experience and
encouraging organic, cross-disciplinary connections, leading to better ideas and thus, ultimately a
more deeply connected world.

#### References:

[1] H. Dombovari, “The importance of networking and creating social capital,” Bachelor of Business
Administration, South-Eastern Finland University of Applied Sciences, 2022. Accessed: Oct. 27,
2023. [Online]. Available: [https://www.theseus.fi/bitstream/handle/10024/748826/Dombovari_Henrik.pdf?sequence=2](https://www.theseus.fi/bitstream/handle/10024/748826/Dombovari_Henrik.pdf?sequence=2)\
[2] “Bluetooth Technology Overview,” Bluetooth® Technology Website. Accessed: Nov. 05, 2023.
[Online]. Available: [https://www.bluetooth.com/learn-about-bluetooth/tech-overview/](https://www.bluetooth.com/learn-about-bluetooth/tech-overview/)\
[3] M. Keimiöniemi, A. Akbar, and N. Nordström, “Networking Bracelet Design Document,” Nov. 09,
2023.

## Interested?

If the idea sounds compelling to you and you believe you would have something to offer, do not hesitate
to reach out via any of the channels listed [here on my website](https://users.aalto.fi/~keimiom1/).
A lot more groundwork has been done in the form of extensive market research, which confirms the idea as
unique, and user research, which positively indicates about its potential viability. If you are interested,
do reach out!

I would be interested in potentially developing the idea further with a co-founder experienced or obsessed
with designing, building and/or manufacturing electronics hardware.
