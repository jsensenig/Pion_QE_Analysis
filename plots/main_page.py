import os
import sys
import time
from flask import Flask, render_template
from ROOT import TFile, TCanvas


app = Flask(__name__)


def open_file(in_file):

    try:
        f = TFile.Open(in_file, 'READ')
        return f
    except FileNotFoundError:
        print("No file found at ", in_file)
        return


def hist_to_image(in_file):

    ifile = open_file(in_file)

    hists = ifile.GetListOfKeys()
    ts = str(time.time())
    images = []

    for h in hists:

        h_name = h.GetName()
        c = TCanvas()
        hist = ifile.Get(h_name)
        hist.Draw("COLZ")

        c.SaveAs("static/" + h_name + "_" + ts + ".png")
        images.append("static/" + h_name + "_" + ts + ".png")

    return images


def remove_stale_imgs():

    for filename in os.listdir('static/'):
        if filename.startswith('h_'):  # not to remove other images
            os.remove('static/' + filename)


def create_template(imgs):

    temp_file = "templates/html_temp.txt"
    html_file = "templates/render_plots.html"

    ofile = open(html_file, "w")

    f = open(temp_file)
    lines = f.readlines()

    for line in lines:
        word = line.split()

        if len(word) > 0:
            if word[0] == '<img':
                for i in imgs:
                    print('<img src="' + i + '" />', file=ofile)
            else:
                print(line, file=ofile)


@app.route("/", methods=['POST', 'GET'])
def run():

    analysis_file = sys.argv[1]

    remove_stale_imgs()
    images = hist_to_image(analysis_file)
    create_template(images)

    return render_template("render_plots.html")


if __name__ == "__main__":

    app.run(debug=True)


