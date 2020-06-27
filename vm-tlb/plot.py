import plotly.graph_objects as go


with open('tlb_measure.dat') as f:
    lines = f.readlines()

x = []
y = []
print(lines)
for line in lines:
    x_a, y_a = line.split()
    x.append(x_a)
    y.append(y_a)


fig = go.Figure(data=go.Scatter(x=x, y=y))
fig.show()