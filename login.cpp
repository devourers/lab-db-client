using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;
 
namespace kursa4
{
    public partial class Login : Form
    {
        public Login()
        {
            InitializeComponent();
        }
 
        private void usrname_Enter(object sender, EventArgs e)
        {
            if (usrname.Text == "username")
            {
                usrname.Text = "";
                usrname.ForeColor = Color.Black;
            }
        }
 
        private void usrname_Leave(object sender, EventArgs e)
        {
            if (usrname.Text == "")
            {
                usrname.Text = "username";
                usrname.ForeColor = Color.DarkGray;
            }
        }
 
        private void pswd_Enter(object sender, EventArgs e)
        {
            if (pswd.Text == "password")
            {
                pswd.Text = "";
                pswd.ForeColor = Color.Black;
            }
        }
 
        private void pswd_Leave(object sender, EventArgs e)
        {
            if (pswd.Text == "")
            {
                pswd.Text = "password";
                pswd.ForeColor = Color.DarkGray;
            }
        }
 
        private void btn_Click(object sender, EventArgs e)
        {
            string user = usrname.Text;
            string pw = pswd.Text;
            string conn = constr.getConnection(user, pw);
            SqlConnection bd = new SqlConnection(conn);
            try
            {
                bd.Open();
                string usr = rolemanager.UserRole(user);
                if (usr == "admin")
                {
                    adminform c = new adminform();
                    this.Hide();
                    c.Show();
                    c.FormClosed += (s, args) => this.Close();
                }
                else if (usr=="labguy")
                {
                   
                    labForm a = new labForm();
                    this.Hide();
                    a.Show();
                    a.FormClosed += (s, args) => this.Close();
                }
                else if(usr=="skladmen")
                {
                    skladform b = new skladform();
                    this.Hide();
                    b.Show();
                    b.FormClosed += (s, args) => this.Close();
                }
            }
            catch (SqlException err)
            {
                Error newForm = new Error(err.Message);
                newForm.Show();
            }
        }
    }
}