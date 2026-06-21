import pandas as pd
import matplotlib.pyplot as plt

from reportlab.platypus import (
    SimpleDocTemplate,
    Paragraph,
    Spacer,
    Image,
    Table,
    TableStyle,
    PageBreak
)

from reportlab.lib import colors
from reportlab.lib.styles import getSampleStyleSheet


csv_file = "results/results.csv"

data = pd.read_csv(csv_file)

graph_file = "results/graph.png"

plt.figure(figsize=(12, 7))

plt.plot(
    data["InputSize"],
    data["InsertTime"],
    marker="o",
    label="Insertion"
)

plt.plot(
    data["InputSize"],
    data["SearchTime"],
    marker="s",
    label="Search"
)

plt.plot(
    data["InputSize"],
    data["DeleteTime"],
    marker="^",
    label="Deletion"
)

plt.title("Red-Black Tree Performance")

plt.xlabel("Input Size")

plt.ylabel("Execution Time (seconds)")

plt.legend()

plt.grid(True)

plt.savefig(
    graph_file,
    dpi=300,
    bbox_inches="tight"
)

plt.close()

print("Graph generated successfully.")

pdf_file = "results/report.pdf"

doc = SimpleDocTemplate(pdf_file)

styles = getSampleStyleSheet()

elements = []


elements.append(
    Paragraph(
        "Red-Black Tree Benchmark Results",
        styles["Title"]
    )
)

elements.append(Spacer(1, 12))


table_data = [[
    "Input Size",
    "Insert Time (s)",
    "Search Time (s)",
    "Delete Time (s)"
]]

for _, row in data.iterrows():
    table_data.append([
        f"{int(row['InputSize'])}",
        f"{row['InsertTime']:.6f}",
        f"{row['SearchTime']:.6f}",
        f"{row['DeleteTime']:.6f}"
    ])

table = Table(table_data)

table.setStyle(
    TableStyle([
        ('BACKGROUND', (0,0), (-1,0), colors.lightgrey),
        ('GRID', (0,0), (-1,-1), 1, colors.black),
        ('FONTNAME', (0,0), (-1,0), 'Helvetica-Bold'),
    ])
)

elements.append(table)

elements.append(PageBreak())

elements.append(
    Paragraph(
        "Performance Graph",
        styles["Heading1"]
    )
)

elements.append(Spacer(1, 12))

elements.append(
    Image(
        graph_file,
        width=500,
        height=300
    )
)

doc.build(elements)

print(f"PDF generated: {pdf_file}")