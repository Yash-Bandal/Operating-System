#!/bin/bash

ADDRESS_BOOK="address_book.txt"

# Function to create the address book
create_address_book() {
    if [[ ! -f $ADDRESS_BOOK ]]; then
        touch $ADDRESS_BOOK
        echo "Address book created."
    else
        echo "Address book already exists."
    fi
}

# Function to view the address book
view_address_book() {
    if [[ -f $ADDRESS_BOOK ]]; then
        echo "Address Book:"
        cat $ADDRESS_BOOK
    else
        echo "Address book does not exist."
    fi
}
search_contact() {
    echo "Enter the name to search:"
    read search_name
    if [ -f  $ADDRESS_BOOK ]; then
        grep -i "$search_name" $ADDRESS_BOOK
    else
        echo "Address book is empty."
    fi
}


# Function to insert a record
insert_record() {
    echo "Enter Name:"
    read name
    echo "Enter Phone Number:"
    read phone
    echo "Enter Email:"
    read email
    echo "$name | $phone | $email" >> $ADDRESS_BOOK
    echo "Record inserted."
}

# Function to delete a record
delete_record() {
    echo "Enter the name of the record to delete:"
    read name
    sed -i.bak "/^$name |/d" $ADDRESS_BOOK
    echo "Record deleted (if it existed)."
}

# Function to modify a record
modify_record() {
  gedit address_book.sh
}

# Main menu
while true; do
    echo "Address Book Menu"
    echo "a) Create Address Book"
    echo "b) View Address Book"
    echo "c) Insert Record"
    echo "d) Delete Record"
    echo "e) Modify Record"
    echo "f) Exit"
    echo "g) search contact"
    read -p "Choose an option: " option

    case $option in
        a) create_address_book ;;
        b) view_address_book ;;
        c) insert_record ;;
        d) delete_record ;;
        e) modify_record ;;
        g) search_contact ;;
        f) exit 0 ;;
        *) echo "Invalid option. Please try again." ;;
    esac
done

#gedit address_book.sh
#chmod +x address_book.sh
#./address_book.sh
