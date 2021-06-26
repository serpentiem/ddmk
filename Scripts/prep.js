let buffer = "";
let bufferSize = 0;

let pos = 0;
let lastPos = pos;

let start = -1;
let end   = -1;

let startArgs = -1;
let endArgs   = -1;

let args = [];
let arg = "";

let helpers = [];



function Feed(size = 1)
{
	c += Substring(buffer, pos, size);
}

function InRange()
{
	if (pos < bufferSize)
	{
		return true;
	}

	return false;
}

function GetTabCount()
{
	let count = 0;

	lastPos = pos;

	pos--;

	while (pos >= 0)
	{
		let name = Substring(buffer, pos, 1);

		if (name.match(/\t/))
		{
			count++;
		}
		else
		{
			break;
		}

		pos--;
	}

	pos = lastPos;

	return count;
}



// Single-line comment does not include terminating glyphs.

// Returns true if a comment is found. Position will then be behind the comment.

function FeedComment(feed = true)
{
	if (pos >= bufferSize)
	{
		return false;
	}

	let start = 0;
	let end   = bufferSize;



	let nextPos = (pos + 1);

	let name = Substring(buffer, pos, 1);
	let nextName = "";

	if (nextPos < bufferSize)
	{
		nextName = Substring(buffer, nextPos, 1);
	}



	if
	(
		(name == "/") &&
		(nextName == "/")
	)
	{
		start = pos;

		pos += 2;

		while (pos < bufferSize)
		{
			let nextPos = (pos + 1);

			let name = Substring(buffer, pos, 1);
			let nextName = "";

			if (nextPos < bufferSize)
			{
				nextName = Substring(buffer, nextPos, 1);
			}

			if
			(
				name.match(/\r/) &&
				nextName.match(/\n/)
			)
			{
				end = pos;

				break;
			}
			else if (name.match(/\n/))
			{
				end = pos;

				break;
			}

			pos++;
		}

		let size = (end - start);

		let comment = Substring(buffer, start, size);

		if (feed)
		{
			c += comment;
		}

		return true;
	}
	else if
	(
		(name == "/") &&
		(nextName == "*")
	)
	{
		start = pos;

		pos += 2;

		while (pos < bufferSize)
		{
			let nextPos = (pos + 1);

			let name = Substring(buffer, pos, 1);
			let nextName = "";

			if (nextPos < bufferSize)
			{
				nextName = Substring(buffer, nextPos, 1);
			}

			if
			(
				(name == "*") &&
				(nextName == "/")
			)
			{
				end = pos;

				break;
			}

			pos++;
		}

		let size = (end - start);

		let comment = Substring(buffer, start, size);

		if (feed)
		{
			c += comment;
		}

		return true;
	}

	return false;
}

function SkipComment()
{
	return FeedComment(false);
}



function GetLineIndex()
{
	let lineIndex = 1;

	for (let index = 0; index < pos; index++)
	{
		let name = Substring(buffer, index, 1);
		if (name.match(/\n/))
		{
			lineIndex++;
		}
	}

	return lineIndex;
}



// All ReplaceFunction functions return true on error.

function ReplaceFunctionOnce
(
	tag,
	func
)
{
	DebugLog(arguments.callee.name + " Start");

	let tagSize = tag.length;

	start = -1;
	end   = -1;

	startArgs = -1;
	endArgs   = -1;

	let scopeLevel = 1;

	args = [];
	arg = "";



	// Find tag.

	while (pos < bufferSize)
	{
		if (FeedComment())
		{
			continue;
		}

		// At this point we know it's not a comment and we are still within bounds.



		// If there is not enough room, feed the remaining buffer and return.

		if ((pos + tagSize) >= bufferSize)
		{
			DebugLog("Not enough room.");

			let size = (bufferSize - pos);

			Feed(size);

			pos += size;

			DebugLog("pos        " + pos);
			DebugLog("bufferSize " + bufferSize);

			return false;
		}



		let name = Substring(buffer, pos, tagSize);
		if (name == tag)
		{
			start = pos;

			break;
		}



		Feed();

		pos++;
	}

	if (start < 0)
	{
		DebugLog("Tag not found. " + tag);

		return false;
	}

	DebugLog("Found tag. " + pos);



	// Verify tag.

	// Back
	if (pos > 0)
	{
		let lastPos = (pos - 1);
		let lastName = buffer.substring(lastPos, (lastPos + 1));

		if (IsFunctionGlyph(lastName))
		{
			DebugLog("Back failed.");

			Feed(tagSize);

			pos += tagSize;

			return false;
		}
	}

	pos += tagSize;



	// Make sure we have at least one character left.

	if (!InRange())
	{
		DebugLog("Out of range.");

		return false;
	}



	// Front
	{
		let name = Substring(buffer, pos, 1);

		if (IsFunctionGlyph(name))
		{
			DebugLog("Front failed.");

			pos = start;

			let size = (tagSize + 1);

			Feed(size);

			pos += size;

			return false;
		}
	}

	// At this point we have a valid tag.



	// Find opening scope.

	while (pos < bufferSize)
	{
		if (SkipComment())
		{
			continue;
		}



		let name = Substring(buffer, pos, 1);
		if (name == "(")
		{
			pos++;

			startArgs = pos;

			break;
		}



		pos++;
	}

	if (startArgs < 0)
	{
		pos = start;

		let lineIndex = GetLineIndex();

		Log(lineIndex + ": Opening scope not found.");

		return true;
	}



	// Find closing scope.

	while (pos < bufferSize)
	{
		if (SkipComment())
		{
			continue;
		}



		let nextPos = (pos + 1);

		let name = Substring(buffer, pos, 1);
		let nextName = "";

		if (nextPos < bufferSize)
		{
			nextName = Substring(buffer, nextPos, 1);
		}

		if (name == "(")
		{
			scopeLevel++;
		}
		else if (name == ")")
		{
			scopeLevel--;
		}

		if (scopeLevel == 0)
		{
			endArgs = pos;

			if (nextName == ";")
			{
				pos += 2;
			}
			else
			{
				pos++;
			}

			end = pos;

			break;
		}



		pos++;
	}

	if (endArgs < 0)
	{
		pos = start;

		let lineIndex = GetLineIndex();

		Log(lineIndex + ": Closing scope not found.");

		return true;
	}

	DebugLog("start " + start);
	DebugLog("end " + end);

	DebugLog("startArgs " + startArgs);
	DebugLog("endArgs " + endArgs);



	// Get args.

	pos = startArgs;

	while (pos < endArgs)
	{
		if (SkipComment())
		{
			continue;
		}



		let name = Substring(buffer, pos, 1);

		if (name == "(")
		{
			scopeLevel++;
		}
		else if (name == ")")
		{
			scopeLevel--;
		}

		if
		(
			(name == ",") &&
			(scopeLevel == 0)
		)
		{
			args.push(arg);

			arg = "";

			pos++;

			continue;
		}

		arg += name;



		pos++;
	}

	if (arg != "")
	{
		args.push(arg);

		arg = "";
	}



	// Clean args.

	for (let argIndex = 0; argIndex < args.length; argIndex++)
	{
		args[argIndex] = Clean(args[argIndex]);
	}



	// Get tab count.

	pos = start;

	tabCount = GetTabCount();

	DebugLog("tabCount " + tabCount);

	// At this point the stream could already differ from the original buffer.
	// So use the stream's size instead of the buffer's position.

	c = Substring(c, 0, (c.length - tabCount));



	// Do stuff.

	if (func(args))
	{
		return true;
	}



	pos = end;

	tabCount = 0; // @Research: Consider lastTabCount.



	DebugLog(arguments.callee.name + " End");

	return false;
}

function ReplaceFunctionLoop
(
	tag,
	func
)
{
	while (pos < bufferSize)
	{
		if
		(
			ReplaceFunctionOnce
			(
				tag,
				func
			)
		)
		{
			return true;
		}
	}

	return false;
}

function ReplaceFunction
(
	tag,
	func
)
{
	ClearAll();

	pos = 0;

	if
	(
		ReplaceFunctionLoop
		(
			tag,
			func
		)
	)
	{
		return true;
	}

	buffer = c;
	bufferSize = c.length;

	return false;
}



function Prep()
{
	for (let helperIndex = 0; helperIndex < helpers.length; helperIndex++)
	{
		let helper = helpers[helperIndex];

		let tag  = helper[0];
		let func = helper[1];

		if
		(
			ReplaceFunction
			(
				tag,
				func
			)
		)
		{
			return true;
		}
	}

	return false;
}
