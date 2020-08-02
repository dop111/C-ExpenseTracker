This was an exercise in design patterns where two different patterns had to be implemented.

The application enables the user to log and keep track of their bank balance, their spendings and other transactions.
The application implements the state pattern and the command pattern.

The state pattern's purpose in this application is to enable the application to switch state during runtime based on how the user manipulates their balance.
For example, the user may start receiving different messages from the application if they drop below a certain
amount or the application may refuse to do certain things in certain states.

The purpose of the command pattern in this application is to make it easier to undo user actions. For example, the user may want to undo logging a purchase.
The command pattern makes this very easy to implement.

The application also has features not related to design patterns like saving and loading the user's log to disk.