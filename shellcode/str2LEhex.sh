echo $1 | od -An -t x1 | sed 's/ /\n/g' | tac | tr -d '\n' | sed -e 's/^0a//' | sed -e 's/^/0x/';
echo ""
