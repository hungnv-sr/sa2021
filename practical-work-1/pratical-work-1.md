# Pratical Work 1

1. List everyone logged in and save the list in a file called
“users” in your own home directory.

    ```
    w -h | awk '{print $1}' >> ./users
    ```

    Command `w` display who is logged in and what they are doing, adding -h will suppress the header and `awk '{print $1}'` is used to keep only the first column (with user name).

    Command `>> ~/users` is used to append the result to file `users` in the root directory.

2. List all processes that are running and add this list to the
end of the “users” file.

    ```
    ps -a >> ./users
    ```

    `ps` command is used to show process status. `-a` option is used to show processes of other users as well. If you want **all** processes, use `-A` or `-ax` to display processes without controlling terminals.

3. List everyone who is logged on sorted by their username

    ```
    w -h | awk '{print $1}' | sort
    ```

    Similar to task 1 to list username, but we add `sort` to sort the result in ascending order (default order).

4. Count number of session each logged in user, sorted by this
number in descending order
    ```
    last | awk '{print $1}'| egrep -v "^(wtmp)?$" | sort | uniq -c| sort -nr
    ```

    `last` command indicates last login of all users.

    `sort` to sort before count.

    `uniq -c` to count the number of login of each user.

    `sort -nr` to sort number in descending order (in this case, `-r` is enough)

5. Show content of the first and last 3 lines of the file
“/etc/fstab”

    ```
    head -3 users && tail -3 users
    ```

    `head -3 users` show first 3 line of `users` file. In my case, their is no file “/etc/fstab” (MacOS).

    `tail -3 users` show last 3 line of `users` file.

6. Retrieve line number 5 to 10 from the file “/etc/fstab” and
write these lines into a new file “extract.txt”

    ```
    sed -n '5,10p' users >> extract.txt
    ```

7. List all files in current directory, recursively, to which the
user has full permissions

    ```
    ls -lAR ./ | grep rwx | grep -v /
    ```

    `ls ./`: list current directory contents (you can skip `./` part.).

    `-l`: show additional information, include permissions.

    `-a`: all files (include file start with `.`) you can skip this since files start with `.` normally do not give full perpissions.

    `-R`: recursively list all files and subdirectories.

    `| grep "^-rwx"`: list only files with full permissions, `rwx` mean full permissions.


8. Compare two files and show percentage of similarities
between them

    I tried to use `diff` but it doesn't work. Luckily, I found a package name `wdiff`

    ```
    brew install wdiff

    wdiff -s extract.txt users
    ```

    If you are using Linux:

    ```
    apt-get install wdiff
    ```

9. Find all files in current directory, recursively, that are at
least 90% similar

    Too hard, skip
