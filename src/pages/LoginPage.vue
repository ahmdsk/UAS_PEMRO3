<template>
    <q-page class="flex flex-center">
        <q-card style="width: 400px;">
            <q-card-section>
                <div class="text-h6 text-center">Masuk ke Monitor Sensor</div>
            </q-card-section>

            <q-card-section>
                <q-input filled v-model="username" label="Username" lazy-rules
                    :rules="[val => !!val || 'Username is required']" />
                <q-input filled v-model="password" label="Password" type="password" lazy-rules
                    :rules="[val => !!val || 'Password is required']" />
            </q-card-section>

            <q-card-actions class="mx-sm">
                <q-btn label="Login" color="primary" @click="login" style="width: 100%; margin: 0px 10px;" />
            </q-card-actions>
        </q-card>
    </q-page>
</template>

<script>
export default {
    data() {
        return {
            username: '',
            password: ''
        };
    },
    methods: {
        login() {
            const hardcodedUser = {
                username: 'admin',
                password: 'admin'
            };

            if (this.username === hardcodedUser.username && this.password === hardcodedUser.password) {
                this.$q.notify({
                    type: 'positive',
                    message: 'Login successful!'
                });
                this.$router.push('/home');
            } else {
                this.$q.notify({
                    type: 'negative',
                    message: 'Invalid username or password'
                });
            }
        }
    }
};
</script>

<style scoped>
.q-page {
    max-width: 600px;
    margin: auto;
}
</style>