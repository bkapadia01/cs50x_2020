import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():

    rows = db.execute("SELECT * FROM account WHERE id=:id", id = session["user_id"])
    users = db.execute("SELECT * FROM users WHERE id=:id", id = session["user_id"])
    cash = (db.execute("SELECT cash FROM users WHERE id=:id", id = session["user_id"]))[0]["cash"]
    balance = '${:,.2f}'.format(cash)

    quotes = []
    total = 0
    for i in rows:
        lookupQuote = lookup(i['symbol'])
        quoteList =  [lookupQuote['symbol'], lookupQuote['name'], i['shares'], usd(lookupQuote['price']), usd(i['shares'] * lookupQuote['price'])]
        quoteAppend = quotes.append(quoteList)
        total += (i['shares'] * lookupQuote['price'])

    print(quotes)
    totalCash = cash
    totalHolding = totalCash + total

    return render_template("index.html", quotes=quotes, totalCash=usd(totalCash), totalHolding = usd(totalHolding))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        if not request.form.get("symbol"):
            return apology("Must enter a quote", 403)

        elif not request.form.get("shares"):
            return apology("Must enter number of shares", 403)

        try:
           val = int(request.form.get("shares"))
        except ValueError:
           return apology("Must enter valid share amount", 403)

        symbol = lookup(request.form.get("symbol"))
        shares = int(request.form.get("shares"))

        try:
           val = symbol["price"]
        except Exception as e:
    	    return apology("Must enter valid stock symbol", 403)
        # except ValueError:
        #   return apology("Must enter valid stock symbol", 403)

        sharesPrice = symbol["price"]
        balance = db.execute("SELECT cash FROM users WHERE id = :id",
                         id = session["user_id"])
        cashBalance = balance[0]["cash"]
        totalCost = shares * symbol["price"]

        if not shares > 0:
            return apology("Please enter positive amount of shares", 403)

        if symbol == True:
            return apology("Please enter valid symbol", 403)

        if totalCost > cashBalance:
            return apology("Not Enough Funds", 403)


        if totalCost <= cashBalance:
            remainingCash = cashBalance - totalCost
            stocksBought = db.execute("SELECT * FROM account WHERE id=:id AND symbol=:symbol", id = session["user_id"], symbol=symbol["symbol"])

            if not stocksBought:
                db.execute("INSERT INTO Account (id, symbol, shares) VALUES (:id, :symbol, :shares)", id = session["user_id"], symbol = symbol["symbol"], shares=shares)
                db.execute("UPDATE users SET cash = :remainingCash WHERE id = :id", id = session["user_id"], remainingCash = remainingCash)
                db.execute("INSERT INTO 'transaction' (id, symbol, shares, price) VALUES (:id, :symbol, :shares, :price)", id = session["user_id"], symbol = symbol["symbol"], shares=shares, price=symbol["price"])
            else:
                updateShare = stocksBought[0]["shares"] + shares
                print(updateShare)
                db.execute("UPDATE Account SET shares = :shares WHERE id = :id AND symbol= :symbol", id = session["user_id"], symbol = symbol["symbol"], shares=updateShare)
                db.execute("UPDATE users SET cash = :remainingCash WHERE id = :id", id = session["user_id"], remainingCash = remainingCash)
                db.execute("INSERT INTO 'transaction' (id, symbol, shares, price) VALUES (:id, :symbol, :shares, :price)", id = session["user_id"], symbol = symbol["symbol"], shares=shares, price=symbol["price"])


        flash("Bought!")
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute("SELECT * FROM 'transaction' WHERE id=:id", id = session["user_id"])

    record = []
    for i in rows:
        transaction =  [i['symbol'], i['shares'], usd(i['price']), i['datetime']]
        recordAppend = record.append(transaction)

    return render_template("history.html", record=record)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":

        if not request.form.get("symbol"):
            return apology("must enter quote", 403)
        symbol =  lookup(request.form.get("symbol"))
        return render_template("quoted.html", symbol=symbol)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must enter username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must enter password", 403)

        # Ensure re-type password was submitted
        elif not request.form.get("confirmation"):
            return apology("must re-type password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username doesn't exist already
        if len(rows) == 1:
            return apology("username already exists", 403)

        # Ensure retype-passwords match
        if request.form.get("confirmation") != request.form.get("password"):
            return apology("Re-typed password does not match", 403)

        username = request.form.get("username")
        hashpass = generate_password_hash(request.form.get("password"))

        db.execute("INSERT INTO users (username, hash) VALUES (:username, :hashpass)", username=username, hashpass=hashpass)

        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))
        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")

        # Check if this is a number
        try:
           val = int(request.form.get("shares"))
        except ValueError:
            return apology("Must enter number of shares", 403)

        sellShares = int(request.form.get("shares"))

        stocksBought = db.execute("SELECT * FROM account WHERE id =: id AND symbol =: symbol", id = session["user_id"], symbol = symbol)
        cash = (db.execute("SELECT cash FROM users WHERE id=:id", id = session["user_id"]))[0]["cash"]
        shares = stocksBought[0]['shares']
        sharesPrice =  lookup(request.form.get("symbol"))["price"]


        balance = db.execute("SELECT cash FROM users WHERE id = :id",
                         id = session["user_id"])
        cashBalance = balance[0]["cash"]

        if not request.form.get("shares"):
            return apology("must enter shares", 403)

        if shares < sellShares:
            return apology("Can not sell more shares than bought", 403)

        elif not (shares - sellShares) == 0:
            updateShares = shares - sellShares
            updateCash = (sharesPrice * sellShares) + cash
            db.execute("UPDATE account SET shares = :shares WHERE id = :id AND symbol= :symbol", id = session["user_id"], symbol = symbol, shares=updateShares)
            db.execute("UPDATE users SET cash = :cash WHERE id = :id", id = session["user_id"], cash=updateCash)
            db.execute("INSERT INTO 'transaction' (id, symbol, shares, price) VALUES (:id, :symbol, :shares, :price)", id = session["user_id"], symbol = symbol, shares=-sellShares, price=sharesPrice)


        elif (shares - sellShares) == 0:
            updateShares = shares - sellShares
            updateCash = (sharesPrice * sellShares) + cash
            db.execute("DELETE FROM account WHERE id = :id AND symbol= :symbol", id = session["user_id"], symbol = symbol)
            db.execute("UPDATE users SET cash = :cash WHERE id = :id", id = session["user_id"], cash=updateCash)
            db.execute("INSERT INTO 'transaction' (id, symbol, shares, price) VALUES (:id, :symbol, :shares, :price)", id = session["user_id"], symbol = symbol, shares=-sellShares, price=sharesPrice)


        flash("Sold!")
        return redirect("/")

    else:
        symbols = db.execute("SELECT symbol FROM account WHERE id =: id", id = session["user_id"])
        res = [ sub['symbol'] for sub in symbols ]

        return render_template("sell.html", symbols = res)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
