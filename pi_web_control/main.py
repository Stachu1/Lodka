from flask import Flask , redirect, url_for, request, render_template
import os, json, sys


app = Flask(__name__)

def set_motors(l,r,t):
    print(f"Left motro: {l} Right motor: {r}, Time: {t}")

@app.route("/")
def home():
    return render_template("home.html")

@app.route("/", methods=["POST", "GET"])
def post():
    command = request.form["command"]
    processed_command = command.upper()
    print(f"{request.remote_addr}: {processed_command}")
    return redirect(url_for("home"))




if __name__ == '__main__':
    print("=================\nRunning on public\n=================")
    app.run(debug=True, host="0.0.0.0", port=5000)