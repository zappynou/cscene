#!/bin/bash

# Initialize parameter variables.
SRC="$1"
DST="$2"

# Make sure the destination exists.
mkdir -p "${DST}"

# Store a list of items to check.
to_check=

# Store a list of items we are already aware of.
already_detected=

# First, fill the to_check list with all executables we find.
to_check="$(find $SRC -name '*.exe')"

# Then extend the search to all libraries too.
to_check="${to_check} $(find $SRC -name '*.dll')"

# Next, process the list.
while test -n "$to_check"; do
    # Pop the first item from the list.
    for item in ${to_check}; do break; done
    to_check="$(echo ${to_check} | sed s,${item},,g)"

    # Log what we're currently resolving....
    #echo "Resolving ${item}..."

    # Read all dependencies.
    while read dllname; do
        # Check if we already know about this one.
        match=$(echo "${already_detected}" | grep -c "${dllname}")
        test $match -gt 0 && continue

        # Log what we're currently looking for...
        #echo "	- Looking for ${dllname}..."

        # We already met this object, save it for later.
        already_detected="${already_detected} ${dllname}"

        # Search for the file path.
        dllpath=$(find /usr -name "${dllname}" 2>/dev/null |head -n1)

        # Check if we've found it.
        test -z "${dllpath}" && continue

        # We found a new item, we need to check it.
        to_check="${to_check} ${dllpath}"

        # Install the item.
        install -m 644 -v -D "${dllpath}" "${DST}"
    done <<< $(strings "${item}" | sed -n 's,^\([^ ]*\.dll\)$,\1,p')
done
