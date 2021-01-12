import uproot
import numpy as np
import plotly.graph_objs as go
from plotly.offline import plot
import sys


def open_file(file_name):
    try:
        file1 = uproot.open(file_name)
        tree = file1["pduneana/beamana"]
    except FileNotFoundError:
        print("Could not find file", file_name)
        return
    return tree


def find_event_idx(tree, run, evt):
    runs = tree["run"].array(library="np")
    events = tree["event"].array(library="np")
    run_event = np.vstack((runs, events)).T

    event_idx = np.where((run_event[:, 0] == run) & (run_event[:, 1] == evt))[0]

    if len(event_idx) > 1:
        print("Found too many matches! Matches =", len(event_idx))
    elif len(event_idx) > 0:
        print("Found run/event match at index", event_idx[0])
    else:
        event_idx = -1
        print("No matches!")

    return event_idx


def plot(tree, event_idx, run, evt, plot_opt):
    beam_marker = {'size': 2, 'color': 'red', 'colorscale': "Viridis", 'opacity': 0.8, 'cmax': 1., 'cmin': 0.}
    daughter_marker = {'size': 2, 'color': 'orange', 'colorscale': "Viridis", 'opacity': 0.8, 'cmax': 1., 'cmin': 0.}
    shower_marker = {'size': 2, 'color': 'green', 'colorscale': "Viridis", 'opacity': 0.8, 'cmax': 1., 'cmin': 0.}

    reco_beam_x = tree["reco_beam_spacePts_X"].array(library="np")[event_idx][0]
    reco_beam_y = tree["reco_beam_spacePts_Y"].array(library="np")[event_idx][0]
    reco_beam_z = tree["reco_beam_spacePts_Z"].array(library="np")[event_idx][0]

    reco_daughter_x = tree["reco_daughter_spacePts_X"].array(library="np")[event_idx][0]
    reco_daughter_y = tree["reco_daughter_spacePts_X"].array(library="np")[event_idx][0]
    reco_daughter_z = tree["reco_daughter_spacePts_X"].array(library="np")[event_idx][0]

    reco_daughter_shower_x = tree["reco_daughter_spacePts_X"].array(library="np")[event_idx][0]
    reco_daughter_shower_y = tree["reco_daughter_spacePts_X"].array(library="np")[event_idx][0]
    reco_daughter_shower_z = tree["reco_daughter_spacePts_X"].array(library="np")[event_idx][0]

    if len(reco_beam_x) < 1:
        print("Empty event, skipping plots!")
        return

    fig = go.Figure()

    # Plot the beam particle
    fig.add_trace(go.Scatter3d(x=reco_beam_x,
                               y=reco_beam_y,
                               z=reco_beam_z,
                               mode='markers',
                               marker=beam_marker
                               )
                  )

    # Plot the reco daughter tracks
    if plot_opt['daughter_track']:
        for x, y, z in zip(reco_daughter_x, reco_daughter_y, reco_daughter_z):
            fig.add_trace(go.Scatter3d(x=x,
                                       y=y,
                                       z=z,
                                       mode='markers',
                                       marker=daughter_marker
                                       )
                          )

    # Plot the reco daughter showers
    if plot_opt['daughter_shower']:
        for x, y, z in zip(reco_daughter_shower_x, reco_daughter_shower_y, reco_daughter_shower_z):
            fig.add_trace(go.Scatter3d(x=x,
                                       y=y,
                                       z=z,
                                       mode='markers',
                                       marker=shower_marker
                                       )
                          )

    title = "Run " + str(run) + " event " + str(evt)
    fig.update_layout(title=title)
    fig.show()


def plot_event(file, run, evt, plot_opt):
    tree = open_file(file)
    if tree is None:
        return

    idx = find_event_idx(tree, run, evt)
    if idx == -1:
        return

    plot(tree, idx, run, evt, plot_opt)


########################################

file = "../../pduneana.root"
run = 13778829
event = 1068
plot_opts = {'daughter_track': True, 'daughter_shower': True}

plot_event(file, run, event, plot_opts)
