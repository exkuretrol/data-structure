from time import sleep
from typing import List, Union

import pandas as pd
import streamlit as st
from homework import Sort  # type: ignore
from plotly import express as px

import redirect as rd
from menu import menu_with_redirect

menu_with_redirect()
st.header("排序")
st.caption("Sort")

sidebar_text_list = list()
sidebar_text_list.append("---")

c1 = st.container(border=True)


@st.cache_resource
def init_sort(n: int, times: int):
    return Sort(n, times)


s = init_sort(1000, 10)


def set_attr(attr: str):
    sleep(0.3)
    attr_val = getattr(st.session_state, attr)
    set_attr = f"set_{attr}"
    setter = getattr(s, set_attr)
    if isinstance(attr_val, int):
        setter(attr_val)
    elif isinstance(attr_val, tuple):
        setter(*attr_val)
    print(f"set attribute {attr} to {attr_val}")


input_n = c1.number_input(
    label="n",
    key="n",
    min_value=10,
    max_value=10**6,
    value=1000,
    on_change=set_attr,
    kwargs={"attr": "n"},
)

input_times = c1.number_input(
    label="execution_times",
    key="execution_times",
    min_value=1,
    max_value=1000,
    value=10,
    on_change=set_attr,
    kwargs={"attr": "execution_times"},
)

input_range = c1.slider(
    label="range",
    min_value=0,
    max_value=10**7,
    value=(0, 10**6),
    step=1000,
    key="range",
    on_change=set_attr,
    kwargs={"attr": "range"},
)


algorithm_dict = {
    0: "selection",
    1: "insertion",
    2: "bubble",
    3: "quick (recursive)",
    4: "quick (iterative)",
    5: "merge (recursive)",
    6: "merge (iterative)",
    7: "heap",
    8: "radix",
}


def set_algorithm_list():
    sleep(0.3)
    l = getattr(st.session_state, "algorithm_list", [])
    active_l = [1 if i in l else 0 for i in range(9)]
    non_active_l = [not i for i in active_l]
    s.set_sort_alg_active_list(active_l)
    st.session_state.non_active_l = non_active_l


input_algorithm_list = c1.multiselect(
    "algorithm_list",
    key="algorithm_list",
    options=list(algorithm_dict.keys()),
    format_func=lambda x: algorithm_dict.get(x),
    default=list(algorithm_dict.keys()),
    on_change=set_algorithm_list,
)
button_run = c1.button("執行")
sidebar_text_list.append(f"`n`：單次排序陣列長度。")
sidebar_text_list.append(f"`execution_times`：排序執行次數。")
sidebar_text_list.append(f"`algorithm_list`：排序演算法。")
sidebar_text_list.append(f"`range`：陣列數字上下界。")


def get_time_it_table() -> pd.DataFrame:
    return pd.DataFrame(s.get_time_it_table())


tab_a, tab_b, tab_c = st.tabs(["log", "time_it_table", "chart"])

if button_run:
    sleep(0.7)
    with tab_a:
        code = st.code(language="css", body="", line_numbers=True)
        with rd.stdout(to=code):
            s.execution_sort()

    df = get_time_it_table()
    df.columns = [algorithm_dict[i] for i in df.columns]
    df.index = [f"{(i + 1)* input_n}" for i in df.index]
    non_active_l = getattr(st.session_state, "non_active_l", [])
    df.drop(df.columns[non_active_l], axis=1, inplace=True)
    with tab_b:
        st.dataframe(df)
    with tab_c:
        fig = px.line(
            df,
            title="執行時間",
            labels={
                "index": "array length",
                "value": "time (micro seconds)",
            },
        )
        fig.update_xaxes(tickvals=df.index)

        fig.update_layout(
            hovermode="x unified",
            legend_title_text="algorithm",
            legend=dict(
                orientation="h", yanchor="bottom", y=1.02, xanchor="right", x=1
            ),
        )

        fig.update_traces(hovertemplate="%{y} microseconds")

        st.plotly_chart(fig)


st.sidebar.markdown("\n\n".join(sidebar_text_list))
