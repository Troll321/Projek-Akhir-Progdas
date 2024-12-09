const fs = require("fs");

const arr = ["interactions", "posts", "transactions", "users", "payments"]

arr.forEach(val => {
	const dir = fs.readdirSync("./database/"+val);
	for (let i = 0; i < dir.length; i++) {
		fs.unlinkSync("./database/"+val+"/"+dir[i]);
	}
});