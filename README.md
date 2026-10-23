This is an old proof of concept codebase. It should be programmed to an arduino to emulate an access.bus mouse, and if you uncomment/comment the right lines in the ino file it can also emulate a keyboard.
The code quality isn't great, as this never moved much beyond proof of concept, but it has worked and even been tested inside an X11 session.

The keyboard capability string is set to match that of a LK501-AA because the DECstation firmware refuses anything else. Don't be tempted by the extensible nature of the access.bus protocol, as DEC did not seem to care much for it.
